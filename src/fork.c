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

t_fork	*init_forks(int nb_philo)
{
	t_fork	*forks;
	int i;

	forks = malloc(sizeof (t_fork) * nb_philo);
	if (forks == NULL)
		return (NULL);
	i = 0;
	while (i < nb_philo)
	{
		i++;
	}
	return (forks);
}
