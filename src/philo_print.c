/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:52:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/02/28 16:52:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	philo_print_fork(t_philo_u_data *u_data)
{
	printf("%zu %zu has taken a fork.\n",
		   get_timestamp(u_data->s_data), u_data->philo_nb);
}

void	philo_print_eat(t_philo_u_data *u_data)
{
	printf("%zu %zu is eating.\n",
		   get_timestamp(u_data->s_data), u_data->philo_nb);
}
