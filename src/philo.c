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
	status = PENDING;
	while(status == PENDING)
	{
		pthread_mutex_lock(&u_data->s_data->status.lock);
		status = u_data->s_data->status.status;
		pthread_mutex_unlock(&u_data->s_data->status.lock);
	}
	while (1)
	{
		philo_eat(u_data);
		philo_sleep(u_data);
		philo_print_think(u_data);
	}
	return (NULL);
}

void	philo_run(t_philo_s_data *s_data, t_philo_u_data *u_data)
{
	size_t			i;

	pthread_mutex_lock(&s_data->status.lock);
	gettimeofday(&s_data->timestamp, NULL);
	s_data->status.status = RUNNING;
	printf("UNLOCK\n");
	pthread_mutex_unlock(&s_data->status.lock);
	i = 0;
	while (i < s_data->philo_total)
	{
		pthread_join(u_data[i].thread_id, NULL);
		i++;
	}
}


void	philo_sleep(t_philo_u_data *u_data)
{
	philo_print_sleep(u_data);
	usleep(u_data->s_data->time_to_sleep * 1000);
}
