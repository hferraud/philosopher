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

size_t	get_timestamp(t_philo_s_data *s_data)
{
	struct timeval	current_time;
	struct timeval	philo_time;
    size_t			timestamp;

	philo_time = s_data->timestamp;
	gettimeofday(&current_time, NULL);
	timestamp = (current_time.tv_sec * 1000.0 - philo_time.tv_sec * 1000.0)
			+ (current_time.tv_usec / 1000.0 - philo_time.tv_usec / 1000.0) + 0.5;
	return (timestamp);
}