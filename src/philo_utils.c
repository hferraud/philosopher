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