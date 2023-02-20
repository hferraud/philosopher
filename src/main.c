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
	t_philo p_data;

	philo_parse(argc, argv, &p_data);
	philo_init(&p_data);
}