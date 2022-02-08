/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_and_finish.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:59:13 by ljohnson          #+#    #+#             */
/*   Updated: 2022/02/07 19:25:29 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ph_check_end(t_prog *program)
{
	int			a;
	int			end_with_plates;
	uint64_t	current_time;
	t_philo		*philo;

	a = 0;
	current_time = ph_get_time();
	end_with_plates = program->nb_plates;
	while (a < program->nb_philo)
	{
		philo = &program->philo[a];
		if (program->nb_plates > -1 && philo->plate_count < program->nb_plates)
			end_with_plates = -1;
		if (current_time - philo->time_of_last_plate > program->time_to_die)
		{
			program->end_of_buffet = 1;
			ph_send_message(philo, "died");
			return (0);
		}
		a++;
	}
	if (end_with_plates > -1)
		return (0);
	return (1);
}

void	ph_wait_end_of_buffet(t_prog *program)
{
	while (1)
	{
		pthread_mutex_lock(&program->status);
		if (!ph_check_end(program))
		{
			program->end_of_buffet = 1;
			pthread_mutex_unlock(&program->status);
			break ;
		}
		pthread_mutex_unlock(&program->status);
	}
}

void	ph_init_philo(t_prog *program)
{
	int		a;
	t_philo	*philo;

	a = 0;
	while (a < program->nb_philo)
	{
		philo = &program->philo[a];
		philo->program = program;
		philo->seat = a + 1;
		philo->time_of_last_plate = program->time_at_start;
		philo->life = 1;
		philo->left_fork = &program->forks[a];
		a++;
		philo->right_fork = &program->forks[a % program->nb_philo];
	}
}

int	ph_init_program(int ac, char **av, t_prog *program)
{
	int	a;

	program->end_of_buffet = 0;
	program->nb_philo = ft_atol(av[1]);
	if (!program->nb_philo)
		return (1);
	program->time_to_die = ft_atol(av[2]);
	program->time_to_eat = ft_atol(av[3]);
	program->time_to_sleep = ft_atol(av[4]);
	program->nb_plates = -1;
	if (ac == 6)
		program->nb_plates = ft_atol(av[5]);
	program->forks = ft_calloc(program->nb_philo, sizeof(pthread_mutex_t));
	program->philo = ft_calloc(program->nb_philo, sizeof(t_philo));
	if (!program->forks || !program->philo)
		return (ph_free(program));
	pthread_mutex_init(&program->status, NULL);
	a = 0;
	while (a < program->nb_philo)
	{
		pthread_mutex_init(&program->forks[a], NULL);
		a++;
	}
	return (0);
}
