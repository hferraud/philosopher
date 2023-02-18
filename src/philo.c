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

static void	philo_init_one(t_philo *p_data);

void	*philo_routine(void *arg)
{
	t_philo		*p_data;

	p_data = (t_philo *) arg;

	return (NULL);
}

void philo_init(t_philo *p_data)
{
	int	i;

	i = 0;
	while(i < p_data->nb_philo)
	{
		philo_init_one(p_data);
		if (errno)
			return ;
		i++;
	}
}

static void	philo_init_one(t_philo *p_data)
{
	pthread_t	thread_id;
	void		*ret;

	pthread_create(&thread_id, NULL, philo_routine, p_data);
	if (errno)
		return ;
	pthread_join(thread_id, &ret);
}
