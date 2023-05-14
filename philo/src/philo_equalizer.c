/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_equalizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 03:56:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/03/10 03:56:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static void	*equalizer_routine(void *arg);
static void	philo_equalize(t_philo_s_data *s_data);

int	philo_equalizer_init(t_philo_s_data *s_data, pthread_t *thread)
{
	s_data->meal_tracker.status
		= malloc(sizeof(t_meal_status) * s_data->philo_total);
	// HERE
	s_data->meal_tracker.meal_time
		= malloc(sizeof(struct timeval) * s_data->philo_total);
	if (s_data->meal_tracker.meal_time == NULL)
		return (-1);
	if (pthread_mutex_init(&s_data->meal_tracker.lock, NULL) != 0)
	{
		free(s_data->meal_tracker.meal_time);
		return (-1);
	}
	if (pthread_create(thread, NULL, equalizer_routine, s_data) != 0)
	{
		free(s_data->meal_tracker.meal_time);
		pthread_mutex_destroy(&s_data->meal_tracker.lock);
		return (-1);
	}
	return (0);
}

static void	*equalizer_routine(void *arg)
{
	t_philo_s_data	*s_data;
	t_status		status;

	s_data = (t_philo_s_data *)arg;
	status = PENDING;
	while (status == PENDING)
	{
		pthread_mutex_lock(&s_data->status.lock);
		status = s_data->status.status;
		pthread_mutex_unlock(&s_data->status.lock);
	}
	while (status == RUNNING)
	{
		philo_equalize(s_data);
		pthread_mutex_lock(&s_data->status.lock);
		status = s_data->status.status;
		pthread_mutex_unlock(&s_data->status.lock);
	}
	return (NULL);
}

static void	philo_equalize(t_philo_s_data *s_data)
{
	size_t		elapsed_time;
	ssize_t		meal_count;
	size_t		i;

	i = 0;
	while (i < s_data->philo_total)
	{
		pthread_mutex_lock(&s_data->meal_tracker.lock);
		elapsed_time = get_elapsed_time(s_data->meal_tracker.meal_time[i]);
		meal_count = s_data->meal_tracker.meal_count[i];
		pthread_mutex_unlock(&s_data->meal_tracker.lock);
		if (s_data->max_meal == -1 || meal_count < s_data->max_meal)
		{
			if (elapsed_time > s_data->time_to_die)
			{
				pthread_mutex_lock(&s_data->status.lock);
				s_data->status.status = INTERRUPTED;
				pthread_mutex_unlock(&s_data->status.lock);
				philo_print_death(s_data, i);
			}
		}
		i++;
	}
}

/**
 * @return True if the status is RUNNING, false otherwise
 */
bool	philo_check_status(t_philo_s_data *s_data)
{
	t_status	status;

	pthread_mutex_lock(&s_data->status.lock);
	status = s_data->status.status;
	pthread_mutex_unlock(&s_data->status.lock);
	return (status == RUNNING);
}

