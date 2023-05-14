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

void	philo_print_fork(t_philo_u_data *u_data)
{
	size_t	t;

	t = get_time_between(u_data->s_data->start_timestamp, u_data->meal_time);
	pthread_mutex_lock(&u_data->s_data->print_lock);
	printf("%s%zu %zu has taken a fork%s\n", AC_YELLOW,
		t, u_data->philo_nb, AC_NORMAL);
	pthread_mutex_unlock(&u_data->s_data->print_lock);
}

void	philo_print_eat(t_philo_u_data *u_data)
{
	size_t	t;

	t = get_time_between(u_data->s_data->start_timestamp, u_data->meal_time);
	pthread_mutex_lock(&u_data->s_data->print_lock);
	printf("%s%zu %zu is eating%s\n", AC_GREEN,
		t, u_data->philo_nb, AC_NORMAL);
	pthread_mutex_unlock(&u_data->s_data->print_lock);
}

void	philo_print_sleep(t_philo_u_data *u_data, struct timeval timestamp)
{
	size_t	t;

	t = get_time_between(u_data->s_data->start_timestamp, timestamp);
	pthread_mutex_lock(&u_data->s_data->print_lock);
	printf("%s%zu %zu is sleeping%s\n", AC_MAGENTA,
		t, u_data->philo_nb, AC_NORMAL);
	pthread_mutex_unlock(&u_data->s_data->print_lock);
}

void	philo_print_think(t_philo_u_data *u_data)
{
	struct timeval	timestamp;

	pthread_mutex_lock(&u_data->s_data->print_lock);
	timestamp = u_data->s_data->start_timestamp;
	printf("%s%zu %zu is thinking%s\n", AC_CYAN,
		get_elapsed_time(timestamp), u_data->philo_nb, AC_NORMAL);
	pthread_mutex_unlock(&u_data->s_data->print_lock);
}

void	philo_print_death(t_philo_s_data *s_data, size_t philo_nb)
{
	struct timeval	timestamp;

	pthread_mutex_lock(&s_data->print_lock);
	timestamp = s_data->start_timestamp;
	printf("%s%zu %zu died%s\n", AC_RED,
		get_elapsed_time(timestamp), philo_nb, AC_NORMAL);
	pthread_mutex_unlock(&s_data->print_lock);
}
