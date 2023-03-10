/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_equalizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 03:56:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/03/10 03:56:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

/**
 * @brief Check whether the philosopher is dead and print the associated message.
 * @return 1 if the philosopher is dead, 0 otherwise.
 * Return -1 if an error occurred.
 */
int	philo_equalizer(t_philo_u_data *u_data)
{
	size_t			elapsed_time;

	elapsed_time = get_elapsed_time(u_data->last_meal);
	if (pthread_mutex_lock(&u_data->s_data->status.lock) != 0)
		return (-1);
	if (u_data->s_data->status.status == INTERRUPTED)
	{
		if (pthread_mutex_unlock(&u_data->s_data->status.lock) != 0)
			return (-1);
		return (1);
	}
	if (elapsed_time > u_data->s_data->time_to_die)
	{
		philo_print_death(u_data);
		u_data->s_data->status.status = INTERRUPTED;
		if (pthread_mutex_unlock(&u_data->s_data->status.lock) != 0)
			return (-1);
		return (1);
	}
	if (pthread_mutex_unlock(&u_data->s_data->status.lock) != 0)
		return (-1);
	return (0);
}
