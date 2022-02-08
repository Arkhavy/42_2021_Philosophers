/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_buffet.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:06:05 by ljohnson          #+#    #+#             */
/*   Updated: 2022/02/07 19:33:59 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ph_send_message(t_philo *philo, char *status)
{
	uint64_t	current_time;

	current_time = ph_get_time() - philo->program->time_at_start;
	printf("%llu %d %s\n", current_time, philo->seat, status);
}

static void	ph_action(t_philo *philo, int id)
{
	pthread_mutex_lock(&philo->program->status);
	if (philo->program->end_of_buffet == 1)
	{
		pthread_mutex_unlock(&philo->program->status);
		return ;
	}
	if (id == PH_FORK)
		ph_send_message(philo, "has taken a fork");
	else if (id == PH_EAT)
	{
		ph_send_message(philo, "is eating");
		philo->time_of_last_plate = ph_get_time();
	}
	else if (id == PH_SLEEP)
	{
		ph_send_message(philo, "is sleeping");
		philo->plate_count++;
	}
	else if (id == PH_THINK)
		ph_send_message(philo, "is thinking");
	pthread_mutex_unlock(&philo->program->status);
}

static void	*ph_table(void *philo_ptr)
{
	t_philo	*philo;

	philo = philo_ptr;
	if (philo->seat % 2 == 0)
		ph_usleep(philo->program, philo->program->time_to_eat * 1000);
	while (!philo->program->end_of_buffet)
	{
		pthread_mutex_lock(philo->left_fork);
		ph_action(philo, PH_FORK);
		if (philo->left_fork == philo->right_fork)
			break ;
		pthread_mutex_lock(philo->right_fork);
		ph_action(philo, PH_FORK);
		ph_action(philo, PH_EAT);
		ph_usleep(philo->program, philo->program->time_to_eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		ph_action(philo, PH_SLEEP);
		ph_usleep(philo->program, philo->program->time_to_sleep * 1000);
		ph_action(philo, PH_THINK);
	}
	if (philo->left_fork == philo->right_fork)
		pthread_mutex_unlock(philo->right_fork);
	return (NULL);
}

int	ph_buffet(t_prog *program)
{
	int		a;
	t_philo	*philo;

	a = 0;
	program->time_at_start = ph_get_time();
	ph_init_philo(program);
	while (a < program->nb_philo)
	{
		philo = &program->philo[a];
		if (pthread_create(&philo->thread_id, NULL, ph_table, philo))
		{
			pthread_mutex_lock(&program->status);
			program->end_of_buffet = 1;
			pthread_mutex_unlock(&program->status);
			return (1);
		}
		a++;
	}
	ph_wait_end_of_buffet(program);
	return (0);
}
