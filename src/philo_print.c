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
#include "print.h"

void	philo_print_fork(t_philo_u_data *u_data)
{
	printf("%s%zu %zu has taken a fork%s\n", AC_YELLOW,
		   get_timestamp(u_data->s_data), u_data->philo_nb, AC_NORMAL);
}

void	philo_print_eat(t_philo_u_data *u_data)
{
	printf("%s%zu %zu is eating%s\n", AC_GREEN,
		   get_timestamp(u_data->s_data), u_data->philo_nb, AC_NORMAL);
}

void	philo_print_sleep(t_philo_u_data *u_data)
{
	printf("%s%zu %zu is sleeping%s\n", AC_MAGENTA,
		   get_timestamp(u_data->s_data), u_data->philo_nb, AC_NORMAL);
}

void	philo_print_think(t_philo_u_data *u_data)
{
	printf("%s%zu %zu is thinking%s\n", AC_CYAN,
		   get_timestamp(u_data->s_data), u_data->philo_nb, AC_NORMAL);
}

void	philo_print_death(t_philo_u_data *u_data)
{
	printf("%s%zu %zu died%s\n", AC_RED,
		   get_timestamp(u_data->s_data), u_data->philo_nb, AC_NORMAL);
}
