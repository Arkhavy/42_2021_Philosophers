/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:54:15 by ljohnson          #+#    #+#             */
/*   Updated: 2022/02/07 19:35:04 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define PH_ERRMESSAGE "\n\e[1m\e[31mError: Incorrect number of args,\
correct utilisation is :\e[0m\n\
\e[32m./philo [number of philo] [time to die] \
[time to eat] [time to sleep] [optional number of plates]\e[0m\n\n"

# define PH_FORK 1
# define PH_EAT 2
# define PH_SLEEP 3
# define PH_THINK 4

typedef struct s_program	t_prog;
typedef struct s_philo		t_philo;

struct s_program
{
	int				nb_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				nb_plates;
	int				end_of_buffet;
	uint64_t		time_at_start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	status;
	t_philo			*philo;
};

struct s_philo
{
	int				seat;
	int				plate_count;
	int				life;
	uint64_t		time_of_last_plate;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_prog			*program;
};

/*/////////////////////////////////////////////////////////////////////////////
		ALL FUNCTIONS
*//////////////////////////////////////////////////////////////////////////////

/*-------------------- philosophers.c --------------------*/

int			ph_exit(t_prog *program);
int			ph_free(t_prog *program);
//int		ph_is_valid(char *av);
//int		ph_check_error(int ac, char **av);
//int		main(int ac, char **av);

/*-------------------- ph_init_and_finish.c --------------------*/

//int		ph_check_end(t_prog *program);
void		ph_wait_end_of_buffet(t_prog *program);
void		ph_init_philo(t_prog *program);
int			ph_init_program(int ac, char **av, t_prog *program);

/*-------------------- ph_buffet.c --------------------*/

void		ph_send_message(t_philo *philo, char *status);
//void		ph_action(t_philo *philo, int id);
//void		*ph_table(void *philo_ptr);
int			ph_buffet(t_prog *program);

/*-------------------- ph_utils.c --------------------*/

void		ph_usleep(t_prog *program, uint64_t time_limit);
uint64_t	ph_get_time(void);
long		ft_atol(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);

#endif //PHILOSOPHERS_H