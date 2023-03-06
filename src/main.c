/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:38:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/01/30 17:38:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int main (int argc, char **argv)
{
	t_philo_s_data	s_data;
	t_philo_u_data 	*u_data;

	philo_parse(argc, argv, &s_data);
	if (errno)
		return (errno);
	u_data = philo_init(&s_data);
	if (u_data == NULL)
		return (errno);
	philo_run(u_data, &s_data);
}