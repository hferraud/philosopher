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

static int	philo_sleep(t_philo_u_data *u_data);

void	*philo_routine(void *arg)
{
	t_philo_u_data	*u_data;
	t_status		status;
	struct timeval	tv;

	u_data = (t_philo_u_data *) arg;
	gettimeofday(&tv, NULL);
	status = PENDING;
	while (status == PENDING)
	{
		if (pthread_mutex_lock(&u_data->s_data->status.lock) != 0)
			return (NULL);
		status = u_data->s_data->status.status;
		if (pthread_mutex_unlock(&u_data->s_data->status.lock) != 0)
			return (NULL);
	}
	u_data->last_meal = u_data->s_data->start_timestamp;
	while (1)
	{
		if (philo_eat(u_data) != 0)
			return (NULL);
		if (philo_sleep(u_data) != 0)
			return (NULL);
		if (philo_print_think(u_data) == -1 || usleep(100) == -1)
			return (NULL);
	}
}

void	philo_run(t_philo_u_data *u_data, t_philo_s_data *s_data)
{
	size_t			i;

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
}

void	philo_exit(t_philo_s_data *s_data)
{
	size_t	i;

	i = 0;
	while(i < s_data->philo_total)
	{
		pthread_mutex_destroy(&s_data->forks->lock);
		i++;
	}
	pthread_mutex_destroy(&s_data->status.lock);
}

/**
 * @brief Check whether the philosopher is dead and print the associated message.
 * @return 1 if the philosopher is dead, 0 otherwise.
 * Return -1 if an error occurred.
 */
int	philo_equalizer(t_philo_u_data *u_data)
{
	size_t			elapsed_time;

	elapsed_time = get_elapsed_time(u_data->last_meal);
	if (pthread_mutex_lock(&u_data->s_data->status.lock) != 0)
		return (-1);
	if (u_data->s_data->status.status == INTERRUPTED)
	{
		if (pthread_mutex_unlock(&u_data->s_data->status.lock) != 0)
			return (-1);
		return (1);
	}
	if (elapsed_time > u_data->s_data->time_to_die)
	{
		philo_print_death(u_data);
		u_data->s_data->status.status = INTERRUPTED;
		if (pthread_mutex_unlock(&u_data->s_data->status.lock) != 0)
			return (-1);
		return (1);
	}
	if (pthread_mutex_unlock(&u_data->s_data->status.lock) != 0)
		return (-1);
	return (0);
}

static int	philo_sleep(t_philo_u_data *u_data)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	if (philo_print_sleep(u_data, timestamp) == -1)
		return (-1);
	if (ft_usleep(timestamp, u_data->s_data->time_to_sleep, u_data) == 1)
		return (1);
	if (errno)
		return (-1);
	return (0);
}
