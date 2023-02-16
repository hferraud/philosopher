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

void	*philo_routine(void *arg)
{
	(void)arg;
	
	printf("test\n");
	return (NULL);
}

void	philo_init(int nb_philo)
{
	pthread_t	thid;
	void		*ret;

	pthread_create(&thid, NULL, philo_routine, &nb_philo);
	pthread_join(thid, &ret);
}
