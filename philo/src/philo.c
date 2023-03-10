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
	philo_start_routine(u_data);
	u_data->last_meal = u_data->s_data->start_timestamp;
	while (1)
	{
		if (philo_eat(u_data, &timestamp) != 0)
			return (NULL);
		if (philo_sleep(u_data, &timestamp) != 0)
			return (NULL);
		if (philo_print_think(u_data) == -1)
			return (NULL);
		if (usleep(20) == -1)
			return (NULL);
	}
}

int	philo_run(t_philo_u_data *u_data, t_philo_s_data *s_data)
{
	size_t			i;

	if (pthread_mutex_lock(&s_data->status.lock) != 0)
		return (-1);
	s_data->status.status = RUNNING;
	gettimeofday(&s_data->start_timestamp, NULL);
	if (pthread_mutex_unlock(&s_data->status.lock) != 0)
		return (-1);
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
	if (philo_equalizer(u_data))
		return (1);
	if (philo_print_sleep(u_data, *timestamp) == -1)
		return (-1);
	if (ft_usleep(*timestamp, u_data->s_data->time_to_sleep, u_data) == 1)
		return (1);
	if (errno)
		return (-1);
	return (0);
}

static int	philo_start_routine(t_philo_u_data *u_data)
{
	t_status		status;

	status = PENDING;
	while (status == PENDING)
	{
		if (pthread_mutex_lock(&u_data->s_data->status.lock) != 0)
			return (-1);
		status = u_data->s_data->status.status;
		if (pthread_mutex_unlock(&u_data->s_data->status.lock) != 0)
			return (-1);
	}
	if (status == INTERRUPTED)
		return (-1);
	return (0);
}
