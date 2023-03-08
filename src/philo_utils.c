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

size_t	get_elapsed_time(struct timeval timestamp)
{
	struct timeval	current_time;
	size_t			elapsed_time;

	gettimeofday(&current_time, NULL);
	elapsed_time = (current_time.tv_sec * 1000.0 - timestamp.tv_sec * 1000.0)
			+ (current_time.tv_usec / 1000.0 - timestamp.tv_usec / 1000.0) + 0.5;
	return (elapsed_time);
}

/**
 * @brief suspend execution for millisecond intervals
 * @return 0 on success, -1 if an error occurred.
 */
int	ft_usleep(struct timeval start_timestamp, size_t duration)
{
	size_t	elapsed_time;

	elapsed_time = get_elapsed_time(start_timestamp);
	printf("elapsed: %zu\nduration: %zu\n", elapsed_time, duration);
	while (elapsed_time <= duration)
	{
		if (usleep(10) == -1)
			return (-1);
		elapsed_time = get_elapsed_time(start_timestamp);
	}
	printf("elapsed: %zu\nduration: %zu\n", elapsed_time, duration);
	return (0);
}
