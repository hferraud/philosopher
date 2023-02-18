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
# include <stdbool.h>
# include <pthread.h>
# include "philo.h"

typedef struct s_fork
{
	int 			nb;
	bool			used;
	pthread_mutex_t	lock;
}					t_fork;

t_fork	*fork_init(t_philo *p_data);

#endif
