/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 22:05:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/03/04 22:05:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static int	philo_use_fork(t_philo_u_data *u_data, t_philo_s_data *s_data);
static void	philo_unuse_fork(t_philo_u_data *u_data, t_philo_s_data *s_data);

int	philo_eat(t_philo_u_data *u_data, struct timeval *timestamp)
{
	t_philo_s_data	*s_data;

	s_data = u_data->s_data;
	if (philo_use_fork(u_data, s_data) == 1)
		return (1);
	pthread_mutex_lock(&s_data->meal_tracker.lock);
	s_data->meal_tracker.meal_time[u_data->philo_nb] = u_data->meal_time;
	s_data->meal_tracker.meal_count[u_data->philo_nb]++;
	pthread_mutex_unlock(&s_data->meal_tracker.lock);
	if (!philo_check_status(s_data))
	{
		philo_unuse_fork(u_data, s_data);
		return (1);
	}
	philo_print_eat(u_data);
	if (ft_usleep(u_data->meal_time, s_data->time_to_eat, u_data) == 1)
		return (1);
	gettimeofday(timestamp, NULL);
	philo_unuse_fork(u_data, s_data);
	return (0);
}

/**
 * @return 1 if forks cannot be accessed, 0 otherwise.
 */
static int	philo_use_fork(t_philo_u_data *u_data, t_philo_s_data *s_data)
{
	size_t	fork1;
	size_t	fork2;

	fork1 = (u_data->philo_nb + u_data->philo_nb % 2) % s_data->philo_total;
	fork2 = (u_data->philo_nb
			+ (u_data->philo_nb + 1) % 2) % s_data->philo_total;
	pthread_mutex_lock(&s_data->forks[fork1]);
	pthread_mutex_lock(&s_data->forks[fork2]);
	if (philo_check_status(s_data))
	{
		gettimeofday(&u_data->meal_time, NULL);
		philo_print_fork(u_data);
		philo_print_fork(u_data);
	}
	else
		return (1);
	return (0);
}

static void	philo_unuse_fork(t_philo_u_data *u_data, t_philo_s_data *s_data)
{
	size_t	fork1;
	size_t	fork2;

	fork1 = (u_data->philo_nb + u_data->philo_nb % 2) % s_data->philo_total;
	fork2 = (u_data->philo_nb
			+ (u_data->philo_nb + 1) % 2) % s_data->philo_total;
	pthread_mutex_unlock(&s_data->forks[fork1]);
	pthread_mutex_unlock(&s_data->forks[fork2]);
}
