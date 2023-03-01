/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 05:07:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/02/20 05:07:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static pthread_t	philo_init_one(t_philo_u_data *u_data);

t_philo_u_data	*philo_init(t_philo_s_data	*s_data)
{
	t_philo_u_data	*u_data;
	size_t			i;

	u_data = malloc(sizeof (t_philo_u_data) * s_data->philo_total);
	if (u_data == NULL)
		return (NULL);
	s_data->forks = fork_init(s_data);
	if (s_data->forks == NULL)
		return (NULL);
	s_data->status.status = PENDING;
	gettimeofday(&s_data->timestamp, NULL);
	pthread_mutex_init(&s_data->status.lock, NULL);
	i = 0;
	while(i < s_data->philo_total)
	{
		u_data[i].philo_nb = i;
		u_data[i].s_data = s_data;
		u_data[i].thread_id = philo_init_one(u_data + i);
		if (errno)
			return (NULL);
		i++;
	}
	return (u_data);
}

static pthread_t	philo_init_one(t_philo_u_data *u_data)
{
	pthread_t		thread_id;

	pthread_create(&thread_id, NULL, philo_routine, u_data);
	return thread_id;
}
