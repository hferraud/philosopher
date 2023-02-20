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

static pthread_t	philo_init_one(t_philo *p_data);

void philo_init(t_philo *p_data)
{
	size_t		i;
	pthread_t	thread_id;

	i = 0;
	p_data->philo_nb = 0;
	p_data->forks = fork_init(p_data);
	p_data->status = PENDING;
	while(i < p_data->philo_total)
	{
		thread_id = philo_init_one(p_data);
		if (errno)
			return ;
		p_data->philo_nb++;
		if (i != p_data->philo_total - 1)
			pthread_detach(thread_id);
		i++;
	}
	pthread_join(thread_id, NULL);
	p_data->status = RUNNING;
	printf("running\n");
}

static pthread_t	philo_init_one(t_philo *p_data)
{
	pthread_t	thread_id;

	pthread_create(&thread_id, NULL, philo_routine, p_data);
	return thread_id;
}
