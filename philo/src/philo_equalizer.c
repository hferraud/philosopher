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
static int	check_meal_tracker(t_philo_s_data *s_data,
				bool *flag, size_t *elapsed_time, size_t i);
static void	interrupt_status(t_philo_s_data *s_data);

int	philo_equalizer_init(t_philo_s_data *s_data, pthread_t *thread)
{
	if (pthread_create(thread, NULL, equalizer_routine, s_data) != 0)
	{
		pthread_mutex_lock(&s_data->status.lock);
		s_data->status.status = INTERRUPTED;
		pthread_mutex_unlock(&s_data->status.lock);
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
	bool		flag;
	size_t		elapsed_time;
	size_t		i;

	i = 0;
	flag = true;
	while (i < s_data->philo_total)
	{
		if (check_meal_tracker(s_data, &flag, &elapsed_time, i) == 1)
			continue ;
		if (elapsed_time > s_data->time_to_die)
		{
			interrupt_status(s_data);
			philo_print_death(s_data, i);
			break ;
		}
		i++;
	}
	if (flag)
		interrupt_status(s_data);
}

/**
 * @return 1 if the philo has not started the simulation, 0 otherwise
 */
static int	check_meal_tracker(t_philo_s_data *s_data,
				bool *flag, size_t *elapsed_time, size_t i)
{
	pthread_mutex_lock(&s_data->meal_tracker.lock[i]);
	if (s_data->meal_tracker.started[i] == false)
	{
		pthread_mutex_unlock(&s_data->meal_tracker.lock[i]);
		return (1);
	}
	if (s_data->max_meal == -1)
		*flag = false;
	else if (s_data->meal_tracker.meal_count[i] < s_data->max_meal)
		*flag = false;
	*elapsed_time = get_elapsed_time(s_data->meal_tracker.meal_time[i]);
	pthread_mutex_unlock(&s_data->meal_tracker.lock[i]);
	return (0);
}

static void	interrupt_status(t_philo_s_data *s_data)
{
	pthread_mutex_lock(&s_data->status.lock);
	s_data->status.status = INTERRUPTED;
	pthread_mutex_unlock(&s_data->status.lock);
}
