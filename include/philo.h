/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:23:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/01/30 18:23:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include "fork.h"
# include "parser.h"

typedef enum e_p_status
{
	PENDING,
	RUNNING
}	t_p_status;

typedef struct s_philo
{
	size_t		philo_nb;
	size_t		philo_total;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	t_fork		*forks;
	t_p_status	status;
}				t_philo;

void philo_init(t_philo *p_data);

#endif
