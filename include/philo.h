/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:23:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/01/30 18:23:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
# include <sys/time.h>
# include "fork.h"
# include "print.h"

typedef struct s_fork t_fork;

typedef enum e_status
{
	PENDING,
	RUNNING,
	SOLVED,
	INTERRUPTED
}	t_status;

typedef struct s_philo_status
{
	t_status		status;
	pthread_mutex_t	lock;
}					t_philo_status;

typedef struct s_philo_s_data
{
	size_t			philo_total;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	ssize_t			max_meal;
	struct timeval	start_timestamp;
	t_fork			*forks;
	t_philo_status	status;
	pthread_mutex_t	print_lock;
}					t_philo_s_data;

typedef struct s_philo_u_data
{
	size_t			philo_nb;
	ssize_t			meal_total;
	struct timeval	meal_time;
	struct timeval	last_meal;
	pthread_t		thread_id;
	t_philo_s_data	*s_data;
}					t_philo_u_data;

void			philo_parse(int argc, char **args, t_philo_s_data *s_data);
t_philo_u_data	*philo_init(t_philo_s_data	*s_data);
void			philo_run(t_philo_u_data *u_data, t_philo_s_data *s_data);
void			*philo_routine(void *arg);
int				philo_eat(t_philo_u_data *u_data);
void			philo_exit(t_philo_s_data *s_data);
int             philo_equalizer(t_philo_u_data *u_data);

size_t	get_elapsed_time(struct timeval timestamp);
size_t	get_time_between(struct timeval start, struct timeval end);
int		ft_usleep(struct timeval start_timestamp, size_t duration, t_philo_u_data *u_data);

#endif
