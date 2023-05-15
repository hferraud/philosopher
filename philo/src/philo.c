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

static int	philo_sleep(t_philo_u_data *u_data, struct timeval *timestamp);
static int	philo_start_routine(t_philo_u_data *u_data);

void	*philo_routine(void *arg)
{
	t_philo_u_data	*u_data;
	struct timeval	timestamp;

	u_data = (t_philo_u_data *) arg;
	if (philo_start_routine(u_data) == 1)
        return (NULL);
	pthread_mutex_lock(&u_data->s_data->meal_tracker.lock);
	u_data->s_data->meal_tracker.meal_time[u_data->philo_nb]
		= u_data->s_data->start_timestamp;
	u_data->s_data->meal_tracker.started[u_data->philo_nb] = true;
	pthread_mutex_unlock(&u_data->s_data->meal_tracker.lock);
	while (1)
	{
		if (philo_eat(u_data, &timestamp) == 1)
			return (NULL);
		if (philo_sleep(u_data, &timestamp) == 1)
			return (NULL);
		if (philo_print_think(u_data) == 1)
            return (NULL);
        usleep(50);
	}
}

int	philo_run(t_philo_u_data *u_data, t_philo_s_data *s_data)
{
	size_t	i;

	pthread_mutex_lock(&s_data->status.lock);
	s_data->status.status = RUNNING;
	gettimeofday(&s_data->start_timestamp, NULL);
	pthread_mutex_unlock(&s_data->status.lock);
	i = 0;
	while (i < s_data->philo_total)
	{
		pthread_join(u_data[i].thread_id, NULL);
		i++;
	}
	if (errno)
		return (-1);
	return (0);
}

static int	philo_sleep(t_philo_u_data *u_data, struct timeval *timestamp)
{
	if (philo_print_sleep(u_data, *timestamp) == 1)
        return (1);
	if (ft_usleep(*timestamp, u_data->s_data->time_to_sleep, u_data) == 1)
		return (1);
	return (0);
}

static int	philo_start_routine(t_philo_u_data *u_data)
{
	t_status		status;

	status = PENDING;
	while (status == PENDING)
	{
		pthread_mutex_lock(&u_data->s_data->status.lock);
		status = u_data->s_data->status.status;
		pthread_mutex_unlock(&u_data->s_data->status.lock);
	}
	if (status == INTERRUPTED)
		return (1);
	return (0);
}
