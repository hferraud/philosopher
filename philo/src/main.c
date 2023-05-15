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

int	main(int argc, char **argv)
{
	t_philo_s_data	s_data;
	t_philo_u_data	*u_data;
	pthread_t		equalizer;

	philo_parse(argc, argv, &s_data);
	if (errno)
		return (1);
	if (s_data.philo_total > PHILO_LIMIT)
		return (printf("Too many philosophers\n"), 1);
	u_data = philo_init(&s_data);
	if (u_data == NULL)
		return (printf("An error occurred\n"), 1);
	if (philo_equalizer_init(&s_data, &equalizer) == -1)
	{
		printf("An error occurred\n");
		return (philo_clear(u_data, &s_data), 1);
	}
	if (philo_run(u_data, &s_data) == -1)
	{
		printf("An error occurred\n");
		return (philo_clear(u_data, &s_data), 1);
	}
	pthread_join(equalizer, NULL);
	philo_clear(u_data, &s_data);
	return (0);
}
