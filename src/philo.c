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

void	philo_sleep(t_philo_u_data *u_data);
int		philo_equalizer(t_philo_u_data *u_data);

void	*philo_routine(void *arg)
{
	t_philo_u_data	*u_data;
	t_status		status;
	struct timeval	tv;

	u_data = (t_philo_u_data *) arg;
	gettimeofday(&tv, NULL);
	status = PENDING;
	while(status == PENDING)
	{
		pthread_mutex_lock(&u_data->s_data->status.lock);
		status = u_data->s_data->status.status;
		pthread_mutex_unlock(&u_data->s_data->status.lock);
	}
	while (1)
	{
		philo_eat(u_data);
		philo_sleep(u_data);
		if (philo_equalizer(u_data))
			return (NULL);
		philo_print_think(u_data);
	}
}

void	philo_run(t_philo_u_data *u_data, t_philo_s_data *s_data)
{
	size_t			i;

	pthread_mutex_lock(&s_data->status.lock);
	s_data->status.status = RUNNING;
	gettimeofday(&s_data->timestamp, NULL);
	pthread_mutex_unlock(&s_data->status.lock);
	i = 0;
	while (i < s_data->philo_total)
	{
		pthread_join(u_data[i].thread_id, NULL);
		i++;
	}
}

/**
 * @brief Check whether the philosopher is dead and print the associated massage.
 * @return 1 if the philosopher is dead, 0 otherwise. Return -1 if an error occurred.
 */
int	philo_equalizer(t_philo_u_data *u_data)
{
	size_t			elapsed_time;

	elapsed_time = get_elapsed_time(u_data->meal_time);
	if (elapsed_time >= u_data->s_data->time_to_die)
	{
		philo_print_death(u_data);
		return (1);
	}
	return (0);
}

void	philo_sleep(t_philo_u_data *u_data)
{
	philo_print_sleep(u_data);
	usleep(u_data->s_data->time_to_sleep * 1000);
}
