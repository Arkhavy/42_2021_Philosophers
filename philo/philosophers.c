/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:58:07 by ljohnson          #+#    #+#             */
/*   Updated: 2022/02/07 19:33:07 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ph_exit(t_prog *program)
{
	int		a;
	t_philo	*philo;

	a = 0;
	while (a < program->nb_philo)
	{
		philo = &program->philo[a];
		pthread_join(philo->thread_id, NULL);
		a++;
	}
	a = 0;
	while (a < program->nb_philo)
	{
		pthread_mutex_destroy(&program->forks[a]);
		a++;
	}
	pthread_mutex_destroy(&program->status);
	return (ph_free(program));
}

int	ph_free(t_prog *program)
{
	if (program->forks)
		free (program->forks);
	if (program->philo)
		free (program->philo);
	return (1);
}

static int	ph_is_valid(char *av)
{
	int	a;

	a = 0;
	if (!av || !av[a])
		return (1);
	while (av[a])
	{
		if (av[a] < '0' || av[a] > '9')
			return (1);
		a++;
	}
	return (0);
}

static int	ph_check_error(int ac, char **av)
{
	int	a;

	a = 1;
	if (ac < 5 || ac > 6)
	{
		write (2, PH_ERRMESSAGE, 181);
		return (1);
	}
	while (av[a])
	{
		if (ph_is_valid(av[a]) == 1)
			return (1);
		a++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_prog	program;

	if (!ph_check_error(ac, av))
	{
		if (ph_init_program(ac, av, &program) == 1)
			return (1);
		if (ph_buffet(&program) == 1)
			return (ph_exit(&program));
	}
	else
		return (1);
	return (ph_exit(&program) * 0);
}
