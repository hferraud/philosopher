/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 09:42:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/02/02 09:42:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "fork.h"

t_fork	*fork_init(int nb_philo)
{
	t_fork	*forks;
	int i;

	forks = malloc(sizeof (t_fork) * nb_philo);
	if (forks == NULL)
		return (NULL);
	i = 0;
	while (i < nb_philo)
	{
		forks[i].nb = i;
		forks[i].used = false;
		pthread_mutex_init(&forks[i].lock, NULL);
		i++;
	}
	return (forks);
}
