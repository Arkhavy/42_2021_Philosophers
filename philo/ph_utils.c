/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:57:47 by ljohnson          #+#    #+#             */
/*   Updated: 2022/02/07 19:13:20 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ph_usleep(t_prog *program, uint64_t	time_limit)
{
	uint64_t	start;

	start = ph_get_time();
	while (ph_get_time() - start < time_limit / 1000)
	{
		if (program->nb_philo < 100)
			usleep(100);
		else
			usleep(1000);
	}
}

uint64_t	ph_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long	ft_atol(const char *str)
{
	long	result;
	size_t	res;
	int		negative;
	int		a;

	negative = 1;
	res = 0;
	a = 0;
	while (str[a] && (str[a] == ' ' || (str[a] >= 9 && str[a] <= 13)))
		a++;
	if (str[a] == '-' || str[a] == '+')
	{
		if (str[a] == '-')
			negative = -negative;
		a++;
	}
	while (str[a] >= '0' && str[a] <= '9')
	{
		res = res * 10 + str[a] - '0';
		a++;
	}
	result = res * negative;
	return (result);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	a;
	char	*str;

	str = s;
	a = 0;
	while (a < n)
	{
		str[a] = '\0';
		a++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	result = malloc(count * size);
	if (!result)
		return (NULL);
	ft_bzero(result, count * size);
	return (result);
}
