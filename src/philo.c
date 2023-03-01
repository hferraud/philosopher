/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:19:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/01/30 19:19:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	philo_eat(t_philo_u_data *u_data);
void	philo_sleep(t_philo_u_data *u_data);

void	*philo_routine(void *arg)
{
	t_philo_u_data	*u_data;
	t_status		status;
	struct timeval	tv;

	u_data = (t_philo_u_data *) arg;
	gettimeofday(&tv, NULL);
	printf("%zu philosopher %zu created.\n",
		   get_timestamp(u_data->s_data), u_data->philo_nb);
	status = PENDING;
	while(status == PENDING)
	{
		pthread_mutex_lock(&u_data->s_data->status.lock);
		status = u_data->s_data->status.status;
		pthread_mutex_unlock(&u_data->s_data->status.lock);
	}
	philo_eat(u_data);
	philo_sleep(u_data);
	return (NULL);
}

void	philo_run(t_philo_s_data *s_data, t_philo_u_data *u_data)
{
	size_t			i;

	pthread_mutex_lock(&u_data->s_data->status.lock);
	u_data->s_data->status.status = RUNNING;
	printf("UNLOCK\n");
	pthread_mutex_unlock(&u_data->s_data->status.lock);
	i = 0;
	while (i < s_data->philo_total)
	{
		pthread_join(u_data[i].thread_id, NULL);
		i++;
	}
}

void	philo_eat(t_philo_u_data *u_data)
{
	t_philo_s_data	*s_data;
	size_t			left_fork;
	size_t			right_fork;

	s_data = u_data->s_data;
	left_fork = u_data->philo_nb;
	right_fork = (u_data->philo_nb + 1) % s_data->philo_total;
	pthread_mutex_lock(&s_data->forks[left_fork].lock);
	pthread_mutex_lock(&s_data->forks[right_fork].lock);
	printf("%zu %zu has taken a fork.\n",
		   get_timestamp(u_data->s_data), u_data->philo_nb);
	printf("\x1b[32m%zu %zu is eating.\x1b[m\n",
		   get_timestamp(u_data->s_data), u_data->philo_nb);
	usleep(u_data->s_data->time_to_eat);
	pthread_mutex_unlock(&s_data->forks[left_fork].lock);
	pthread_mutex_unlock(&s_data->forks[right_fork].lock);
}

void	philo_sleep(t_philo_u_data *u_data)
{
	printf("%zu is sleeping\n", u_data->philo_nb);
	usleep(u_data->s_data->time_to_sleep);
}
