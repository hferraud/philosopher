/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 03:39:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/05/15 03:39:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static void	meal_tracker_clear(t_philo_s_data *s_data);

void	philo_clear(t_philo_u_data *u_data, t_philo_s_data *s_data)
{
	pthread_mutex_destroy(&s_data->status.lock);
	pthread_mutex_destroy(&s_data->print_lock);
	meal_tracker_clear(s_data);
	fork_clear(s_data);
	if (u_data)
		free(u_data);
}

static void	meal_tracker_clear(t_philo_s_data *s_data)
{
	size_t	i;

	free(s_data->meal_tracker.meal_count);
	free(s_data->meal_tracker.meal_time);
	i = 0;
	while (i < s_data->philo_total)
	{
		pthread_mutex_destroy(&s_data->meal_tracker.lock[i]);
		i++;
	}
	free(s_data->meal_tracker.lock);
}
