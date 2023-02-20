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

void	philo_eat(t_philo *p_data);
void	philo_sleep(t_philo *p_data);

void	*philo_routine(void *arg)
{
	t_philo		*p_data;

	p_data = (t_philo *) arg;
	printf("in thread%zu\n",p_data->philo_nb);
	while (p_data->status == PENDING)
		usleep(5);
	philo_eat(p_data);
	philo_sleep(p_data);
	return (NULL);
}

void	philo_eat(t_philo *p_data)
{
	size_t	left_fork;
	size_t	right_fork;

	left_fork = p_data->philo_nb;
	right_fork = (p_data->philo_nb + 1) % p_data->philo_total;
	pthread_mutex_lock(&p_data->forks[left_fork].lock);
	pthread_mutex_lock(&p_data->forks[right_fork].lock);
	printf("%zu is eating\n", p_data->philo_nb);
	usleep(p_data->time_to_eat);
	pthread_mutex_unlock(&p_data->forks[left_fork].lock);
	pthread_mutex_unlock(&p_data->forks[right_fork].lock);
}

void	philo_sleep(t_philo *p_data)
{
	printf("%zu is sleeping\n", p_data->philo_nb);
	usleep(p_data->time_to_sleep);
}
