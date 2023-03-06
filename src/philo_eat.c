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

static int philo_access_fork(t_philo_u_data *u_data, t_philo_s_data *s_data);
//static int philo_access_one_fork(t_philo_u_data *u_data, size_t fork_nb);
static int philo_unaccess_fork(t_philo_u_data *u_data, t_philo_s_data *s_data);
static int	philo_unaccess_one_fork(t_philo_s_data *s_data, size_t fork_nb);

void	philo_eat(t_philo_u_data *u_data)
{
	t_philo_s_data	*s_data;

	s_data = u_data->s_data;
	philo_access_fork(u_data, s_data);
	philo_print_eat(u_data);
	gettimeofday(&u_data->meal_time, NULL);
	usleep(u_data->s_data->time_to_eat * 1000);
	philo_unaccess_fork(u_data, s_data);
}

static int philo_access_fork(t_philo_u_data *u_data, t_philo_s_data *s_data)
{
	size_t			left_fork;
	size_t			right_fork;
	bool			flag;

	left_fork = u_data->philo_nb;
	right_fork = (u_data->philo_nb + 1) % s_data->philo_total;
	flag = false;
	while (!flag)
	{
		pthread_mutex_lock(&s_data->forks[left_fork].lock);
		if (s_data->forks[left_fork].use == UNUSED)
		{
			pthread_mutex_lock(&s_data->forks[right_fork].lock);
			if (s_data->forks[right_fork].use == UNUSED)
			{
				s_data->forks[left_fork].use = USED;
				philo_print_fork(u_data);
				s_data->forks[right_fork].use = USED;
				philo_print_fork(u_data);
				flag = true;
			}
			pthread_mutex_unlock(&s_data->forks[right_fork].lock);
		}
		pthread_mutex_unlock(&s_data->forks[left_fork].lock);
	}
	return (0);
}

static int philo_unaccess_fork(t_philo_u_data *u_data, t_philo_s_data *s_data)
{
	size_t			left_fork;
	size_t			right_fork;

	left_fork = u_data->philo_nb;
	right_fork = (u_data->philo_nb + 1) % s_data->philo_total;

	if (philo_unaccess_one_fork(s_data, left_fork) == -1)
		return (-1);
	if (philo_unaccess_one_fork(s_data, right_fork) == -1)
		return (-1);
	return (0);
}

static int	philo_unaccess_one_fork(t_philo_s_data *s_data, size_t fork_nb)
{
	if (pthread_mutex_lock(&s_data->forks[fork_nb].lock) != 0)
		return (-1);
	s_data->forks[fork_nb].use = UNUSED;
	if (pthread_mutex_unlock(&s_data->forks[fork_nb].lock) != 0)
		return (-1);
	return (0);
}