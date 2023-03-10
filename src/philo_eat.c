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

static int	philo_access_fork(t_philo_u_data *u_data, t_philo_s_data *s_data);
static int	philo_use_fork(t_philo_u_data *u_data, t_philo_s_data *s_data,
				size_t fork1, size_t fork2);
static int	philo_unuse_fork(t_philo_u_data *u_data, t_philo_s_data *s_data);

int	philo_eat(t_philo_u_data *u_data)
{
	t_philo_s_data	*s_data;

	s_data = u_data->s_data;
	if (philo_access_fork(u_data, s_data) == 1)
		return (1);
	else if (errno)
		return (-1);
	u_data->last_meal = u_data->meal_time;
	u_data->meal_total++;
	philo_print_eat(u_data);
	if (ft_usleep(u_data->last_meal, s_data->time_to_eat, u_data) == 1)
		return (1);
	if (errno)
		return (-1);
	if (philo_unuse_fork(u_data, s_data) == -1)
		return (-1);
	if (s_data->max_meal != -1 && u_data->meal_total == s_data->max_meal)
		return (1);
	return (0);
}

/**
 * @return 1 if forks cannot be accessed, 0 otherwise.
 * Return -1 if an error occured
 */
static int	philo_access_fork(t_philo_u_data *u_data, t_philo_s_data *s_data)
{
	size_t	fork1;
	size_t	fork2;
	int		flag;

	fork1 = (u_data->philo_nb + u_data->philo_nb % 2) % s_data->philo_total;
	fork2 = (u_data->philo_nb + (u_data->philo_nb + 1) % 2)
		% s_data->philo_total;
	flag = false;
	while (!flag)
	{
		if (philo_equalizer(u_data))
			return (1);
		if (fork1 != fork2)
			flag = philo_use_fork(u_data, s_data, fork1, fork2);
		if (flag == -1)
			return (-1);
	}
	return (0);
}

static int	philo_use_fork(t_philo_u_data *u_data, t_philo_s_data *s_data,
				size_t fork1, size_t fork2)
{
	int	ret;

	ret = 0;
	if (s_data->forks[fork1].use == UNUSED)
	{
		gettimeofday(&u_data->meal_time, NULL);
		if (pthread_mutex_lock(&s_data->forks[fork1].lock) != 0)
			return (-1);
		if (pthread_mutex_lock(&s_data->forks[fork2].lock) != 0)
			return (-1);
		if (s_data->forks[fork2].use == UNUSED)
		{
			s_data->forks[fork1].use = USED;
			philo_print_fork(u_data);
			s_data->forks[fork2].use = USED;
			philo_print_fork(u_data);
			ret = 1;
		}
		if (pthread_mutex_unlock(&s_data->forks[fork2].lock) != 0)
			return (-1);
	}
	if (pthread_mutex_unlock(&s_data->forks[fork1].lock) != 0)
		return (-1);
	return (ret);
}

static int	philo_unuse_fork(t_philo_u_data *u_data, t_philo_s_data *s_data)
{
	size_t			left_fork;
	size_t			right_fork;

	left_fork = u_data->philo_nb;
	right_fork = (u_data->philo_nb + 1) % s_data->philo_total;
	if (pthread_mutex_lock(&s_data->forks[left_fork].lock) != 0)
		return (-1);
	s_data->forks[left_fork].use = UNUSED;
	if (pthread_mutex_unlock(&s_data->forks[left_fork].lock) != 0)
		return (-1);
	if (pthread_mutex_lock(&s_data->forks[right_fork].lock) != 0)
		return (-1);
	s_data->forks[right_fork].use = UNUSED;
	if (pthread_mutex_unlock(&s_data->forks[right_fork].lock) != 0)
		return (-1);
	return (0);
}
