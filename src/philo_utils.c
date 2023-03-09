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

static size_t	time_to_msec(struct timeval timestamp);

/**
 * @brief suspend execution for millisecond intervals
 * @return 0 on success, -1 if an error occurred.
 */
int	ft_usleep(struct timeval start_timestamp, size_t duration, t_philo_u_data *u_data)
{
	size_t	elapsed_time;

	elapsed_time = get_elapsed_time(start_timestamp);
	while (elapsed_time < duration)
	{
		if (philo_equalizer(u_data))
			return (1);
		elapsed_time = get_elapsed_time(start_timestamp);
	}
	return (0);
}

size_t	get_time_between(struct timeval start, struct timeval end)
{
	return (time_to_msec(end) - time_to_msec(start));
}

size_t	get_elapsed_time(struct timeval timestamp)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (get_time_between(timestamp, current_time));
}

static size_t	time_to_msec(struct timeval timestamp)
{
	size_t	m_sec;

	m_sec = timestamp.tv_sec * (long) 1000
			+ timestamp.tv_usec / (long) 1000.0
			+ (long) 0.5;
	return (m_sec);
}