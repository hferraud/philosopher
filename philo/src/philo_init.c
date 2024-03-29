/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 05:07:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/02/20 05:07:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static int			philo_preset(t_philo_u_data **u_data,
						t_philo_s_data *s_data);
static int			init_meal_tracker(t_philo_s_data *s_data);
static int			init_meal_tracker_lock(t_philo_s_data *s_data);
static pthread_t	philo_init_one(t_philo_u_data *u_data);

t_philo_u_data	*philo_init(t_philo_s_data	*s_data)
{
	t_philo_u_data	*u_data;
	size_t			i;

	u_data = NULL;
	if (philo_preset(&u_data, s_data) == -1)
		return (NULL);
	i = 0;
	while (i < s_data->philo_total)
	{
		u_data[i].philo_nb = i;
		s_data->meal_tracker.started[i] = false;
		s_data->meal_tracker.meal_count[i] = 0;
		u_data[i].s_data = s_data;
		u_data[i].thread_id = philo_init_one(u_data + i);
		if (errno)
		{
			pthread_mutex_lock(&s_data->status.lock);
			s_data->status.status = INTERRUPTED;
			pthread_mutex_unlock(&s_data->status.lock);
			return (NULL);
		}
		i++;
	}
	return (u_data);
}

static int	philo_preset(t_philo_u_data **u_data, t_philo_s_data *s_data)
{
	*u_data = malloc(sizeof (t_philo_u_data) * s_data->philo_total);
	if (*u_data == NULL)
		return (-1);
	s_data->forks = fork_init(s_data);
	if (s_data->forks == NULL)
		return (free(*u_data), -1);
	s_data->status.status = PENDING;
	if (pthread_mutex_init(&s_data->status.lock, NULL) != 0)
		return (free(*u_data), fork_clear(s_data), -1);
	if (pthread_mutex_init(&s_data->print_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&s_data->status.lock);
		return (free(*u_data), fork_clear(s_data), -1);
	}
	if (init_meal_tracker(s_data) == -1)
	{
		pthread_mutex_destroy(&s_data->status.lock);
		pthread_mutex_destroy(&s_data->print_lock);
		return (free(*u_data), fork_clear(s_data), -1);
	}
	return (0);
}

static int	init_meal_tracker(t_philo_s_data *s_data)
{
	s_data->meal_tracker.meal_count
		= malloc(sizeof(ssize_t) * s_data->philo_total);
	if (s_data->meal_tracker.meal_count == NULL)
		return (-1);
	s_data->meal_tracker.meal_time
		= malloc(sizeof(struct timeval) * s_data->philo_total);
	if (s_data->meal_tracker.meal_time == NULL)
	{
		free(s_data->meal_tracker.meal_count);
		return (-1);
	}
	if (init_meal_tracker_lock(s_data) == -1)
	{
		free(s_data->meal_tracker.meal_count);
		free(s_data->meal_tracker.meal_time);
		return (-1);
	}
	return (0);
}

static int	init_meal_tracker_lock(t_philo_s_data *s_data)
{
	size_t	i;

	s_data->meal_tracker.lock
		= malloc(sizeof(pthread_mutex_t) * s_data->philo_total);
	if (s_data->meal_tracker.lock == NULL)
		return (-1);
	i = 0;
	while (i < s_data->philo_total)
	{
		if (pthread_mutex_init(&s_data->meal_tracker.lock[i], NULL) != 0)
		{
			while (i)
			{
				i--;
				pthread_mutex_destroy(&s_data->meal_tracker.lock[i]);
			}
			free(s_data->meal_tracker.lock);
			return (-1);
		}
		i++;
	}
	return (0);
}

static pthread_t	philo_init_one(t_philo_u_data *u_data)
{
	pthread_t	thread_id;

	errno = pthread_create(&thread_id, NULL, philo_routine, u_data);
	return (thread_id);
}
