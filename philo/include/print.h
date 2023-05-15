/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:42:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/03/01 16:42:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef PRINT_H
# define PRINT_H

# define AC_RED "\x1b[31m"
# define AC_GREEN "\x1b[32m"
# define AC_YELLOW "\x1b[33m"
# define AC_MAGENTA "\x1b[35m"
# define AC_CYAN "\x1b[36m"
# define AC_NORMAL "\x1b[m"

# include "philo.h"

typedef struct s_philo_u_data	t_philo_u_data;
typedef struct s_philo_s_data	t_philo_s_data;

int		philo_print_fork(t_philo_u_data *u_data);
int		philo_print_eat(t_philo_u_data *u_data);
int		philo_print_sleep(t_philo_u_data *u_data, struct timeval timestamp);
int		philo_print_think(t_philo_u_data *u_data);
void	philo_print_death(t_philo_s_data *s_data, size_t philo_nb);

#endif
