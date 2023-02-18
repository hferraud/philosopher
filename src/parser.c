/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 21:11:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/02/16 21:11:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static size_t	ft_atoll(const char *str);
static bool		is_digit(char c);

t_philo	philo_parse(int argc, char **args)
{
	t_philo p_data;

	if (argc != 5)
	{
		errno = EINVAL;
		return (p_data);
	}
	p_data.philo_total = ft_atoll(args[1]);
	p_data.time_to_die = ft_atoll(args[2]);
	p_data.time_to_eat = ft_atoll(args[3]);
	p_data.time_to_sleep = ft_atoll(args[4]);
	return (p_data);
}

static size_t	ft_atoll(const char *str)
{
	size_t	nb;

	nb = 0;
	while (*str)
	{
		if (!is_digit(*str))
		{
			errno = EINVAL;
			return (0);
		}
		if ((nb * 10 + (*str - '0')) / 10 != nb)
		{
			errno = EOVERFLOW;
			return (0);
		}
		nb = nb * 10 + (*str - '0');
	}
	return (nb);
}

static bool is_digit(char c)
{
	return (c > '0' && c < '9');
}