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
static int philo_access_one_fork(t_philo_u_data *u_data, size_t fork_nb);

void	philo_eat(t_philo_u_data *u_data)
{
	t_philo_s_data	*s_data;

	s_data = u_data->s_data;
	philo_print_eat(u_data);
	usleep(u_data->s_data->time_to_eat * 1000);
}

static int philo_access_fork(t_philo_u_data *u_data, t_philo_s_data *s_data)
{
	size_t			left_fork;
	size_t			right_fork;
	int				flag[2];

	left_fork = u_data->philo_nb;
	right_fork = (u_data->philo_nb + 1) % s_data->philo_total;
	flag[LEFT] = false;
	flag[RIGHT] = false;
	while ((flag[LEFT] != true || flag[RIGHT] != true))
	{
		if (flag[LEFT] == false)
		{
			flag[LEFT] = philo_access_one_fork(u_data, left_fork);
			if (flag[LEFT] == -1)
				return (-1);
		}
		if (flag[RIGHT] == false)
		{
			flag[RIGHT] = philo_access_one_fork(u_data, right_fork);
			if (flag[RIGHT] == -1)
				return (-1);
		}
	}
}

/**
 * @return 1 if the fork was unused, 0 otherwise. Return -1 if an error occured.
 */
static int philo_access_one_fork(t_philo_u_data *u_data, size_t fork_nb)
{
	t_philo_s_data	*s_data;

	s_data = u_data->s_data;
	if (pthread_mutex_lock(&s_data->forks[fork_nb].lock) != 0)
		return (-1);
	if (s_data->forks[fork_nb].use == UNUSED)
	{
		s_data->forks[fork_nb].use = USED;
		philo_print_fork(u_data);
		if (pthread_mutex_unlock(&s_data->forks[fork_nb].lock) != 0)
			return (-1);
		return (1);
	}
	else
	{
		if (pthread_mutex_unlock(&s_data->forks[fork_nb].lock) != 0)
			return (-1);
		return (0);
	}
}

static int philo_unaccess_fork(t_philo_u_data *u_data)
{
	size_t			left_fork;
	size_t			right_fork;
	t_philo_s_data	*s_data;

	s_data = u_data->s_data;
	left_fork = u_data->philo_nb;
	right_fork = (u_data->philo_nb + 1) % s_data->philo_total;

	pthread_mutex_lock(&s_data->forks[left_fork].lock);
	s_data->forks[left_fork].use = UNUSED;
	pthread_mutex_unlock(&s_data->forks[left_fork].lock);
	pthread_mutex_lock(&s_data->forks[right_fork].lock);
	s_data->forks[right_fork].use = UNUSED;
	pthread_mutex_unlock(&s_data->forks[right_fork].lock);
}
