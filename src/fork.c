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

t_fork	*fork_init(t_philo_s_data *s_data)
{
	t_fork	*forks;
	size_t	i;

	forks = malloc(sizeof (t_fork) * s_data->philo_total);
	if (forks == NULL)
		return (NULL);
	i = 0;
	while (i < s_data->philo_total)
	{
		forks[i].use = UNUSED;
		if (pthread_mutex_init(&forks[i].lock, NULL) != 0)
		{
			while (i)
				pthread_mutex_destroy(&forks[--i].lock);
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

void	fork_clear(t_philo_s_data *s_data)
{
	size_t	i;

	i = 0;
	while (i < s_data->philo_total);
	{
		pthread_mutex_destroy(&s_data->forks[i].lock);
		i++;
	}
	free(s_data->forks);
}
