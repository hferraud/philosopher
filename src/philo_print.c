/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:52:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/02/28 16:52:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "print.h"

int	philo_print_fork(t_philo_u_data *u_data)
{
	size_t	t;

	t = get_time_between(u_data->s_data->start_timestamp, u_data->meal_time);
	if (pthread_mutex_lock(&u_data->s_data->print_lock) != 0)
		return (-1);
	printf("%s%zu %zu has taken a fork%s\n", AC_YELLOW,
		t, u_data->philo_nb, AC_NORMAL);
	if (pthread_mutex_unlock(&u_data->s_data->print_lock) != 0)
		return (-1);
	return (0);
}

int	philo_print_eat(t_philo_u_data *u_data)
{
	size_t	t;

	t = get_time_between(u_data->s_data->start_timestamp, u_data->meal_time);
	if (pthread_mutex_lock(&u_data->s_data->print_lock) != 0)
		return (-1);
	printf("%s%zu %zu is eating%s\n", AC_GREEN,
		t, u_data->philo_nb, AC_NORMAL);
	if (pthread_mutex_unlock(&u_data->s_data->print_lock) != 0)
		return (-1);
	return (0);
}

int	philo_print_sleep(t_philo_u_data *u_data, struct timeval timestamp)
{
	size_t	timer;

	timer = get_time_between(u_data->s_data->start_timestamp, timestamp);
	if (pthread_mutex_lock(&u_data->s_data->print_lock) != 0)
		return (-1);
	printf("%s%zu %zu is sleeping%s\n", AC_MAGENTA,
		timer, u_data->philo_nb, AC_NORMAL);
	if (pthread_mutex_unlock(&u_data->s_data->print_lock) != 0)
		return (-1);
	return (0);
}

int	philo_print_think(t_philo_u_data *u_data)
{
	struct timeval	timestamp;

	if (pthread_mutex_lock(&u_data->s_data->print_lock) != 0)
		return (-1);
	timestamp = u_data->s_data->start_timestamp;
	printf("%s%zu %zu is thinking%s\n", AC_CYAN,
		get_elapsed_time(timestamp), u_data->philo_nb, AC_NORMAL);
	if (pthread_mutex_unlock(&u_data->s_data->print_lock) != 0)
		return (-1);
	return (0);
}

int	philo_print_death(t_philo_u_data *u_data)
{
	struct timeval	timestamp;

	if (pthread_mutex_lock(&u_data->s_data->print_lock) != 0)
		return (-1);
	timestamp = u_data->s_data->start_timestamp;
	printf("%s%zu %zu died%s\n", AC_RED,
		get_elapsed_time(timestamp), u_data->philo_nb, AC_NORMAL);
	if (pthread_mutex_unlock(&u_data->s_data->print_lock) != 0)
		return (-1);
	return (0);
}
