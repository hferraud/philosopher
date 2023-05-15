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

typedef struct s_philo_s_data	t_philo_s_data;

pthread_mutex_t	*fork_init(t_philo_s_data *s_data);
void			fork_clear(t_philo_s_data *s_data);

#endif
