/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 09:43:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/02/02 09:43:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef FORK_H
# define FORK_H

# include <stdlib.h>
# include <pthread.h>
# include "philo.h"

typedef struct s_philo_s_data t_philo_s_data;

enum
{
	LEFT = 0,
	RIGHT = 1
};

typedef enum
{
	USED,
	UNUSED
}t_use;

typedef struct s_fork
{
	size_t			nb;
	t_use			use;
	pthread_mutex_t	lock;
}					t_fork;

t_fork	*fork_init(t_philo_s_data *s_data);

#endif
