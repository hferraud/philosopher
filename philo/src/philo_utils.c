/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:32:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/02/28 16:32:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

/**
 * @return True if the status is RUNNING, false otherwise
 */
bool	philo_check_status(t_philo_s_data *s_data)
{
	t_status	status;

	pthread_mutex_lock(&s_data->status.lock);
	status = s_data->status.status;
	pthread_mutex_unlock(&s_data->status.lock);
	return (status == RUNNING);
}

void	philo_wait(t_philo_u_data *u_data)
{
	t_status		status;

	status = RUNNING;
	while (status == RUNNING)
	{
		pthread_mutex_lock(&u_data->s_data->status.lock);
		status = u_data->s_data->status.status;
		pthread_mutex_unlock(&u_data->s_data->status.lock);
	}
}
