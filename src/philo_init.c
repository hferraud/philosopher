/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 05:07:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/02/20 05:07:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static int			philo_preset(t_philo_u_data *u_data, t_philo_s_data *s_data);
static pthread_t	philo_init_one(t_philo_u_data *u_data);
static void			philo_init_error(t_philo_s_data *s_data);

t_philo_u_data	*philo_init(t_philo_s_data	*s_data)
{
	t_philo_u_data	*u_data;
	size_t			i;

	u_data = NULL;
	if (philo_preset(u_data, s_data) == -1)
		return (NULL);
	i = 0;
	while (i < s_data->philo_total)
	{
		u_data[i].philo_nb = i;
		u_data[i].s_data = s_data;
		u_data[i].thread_id = philo_init_one(u_data + i);
		if (errno)
			return (philo_init_error(s_data), NULL);
		i++;
	}
	return (u_data);
}

static int	philo_preset(t_philo_u_data *u_data, t_philo_s_data *s_data)
{
	u_data = malloc(sizeof (t_philo_u_data) * s_data->philo_total);
	if (u_data == NULL)
		return (-1);
	s_data->forks = fork_init(s_data);
	if (s_data->forks == NULL)
	{
		free(u_data);
		return (-1);
	}
	s_data->status.status = PENDING;
	if (pthread_mutex_init(&s_data->status.lock, NULL) != 0)
	{
		free(u_data);
		fork_clear(s_data);
		return (-1);
	}
	if (pthread_mutex_init(&s_data->print_lock, NULL) != 0)
	{
		free(u_data);
		fork_clear(s_data);
		pthread_mutex_destroy(&s_data->status.lock);
		return (-1);
	}
	return (0);
}

static pthread_t	philo_init_one(t_philo_u_data *u_data)
{
	pthread_t		thread_id;

	u_data->meal_total = 0;
	errno = pthread_create(&thread_id, NULL, philo_routine, u_data);
	return (thread_id);
}

void	philo_clear(t_philo_u_data *u_data, t_philo_s_data *s_data)
{
	pthread_mutex_destroy(&s_data->status.lock);
	pthread_mutex_destroy(&s_data->print_lock);
	fork_clear(s_data);
	if (u_data)
		free(u_data);
}

static void	philo_init_error(t_philo_s_data *s_data)
{
	pthread_mutex_lock(&s_data->status.lock);
	s_data->status.status = INTERRUPTED;
	pthread_mutex_unlock(&s_data->status.lock);
}
