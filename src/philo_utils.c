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

__suseconds_t	get_timestamp(t_philo_s_data *s_data)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec - s_data->timestamp.tv_usec);
}