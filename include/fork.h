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

typedef struct s_fork
{
	bool			used;
	pthread_mutex_t	lock;
}					t_fork;

#endif
