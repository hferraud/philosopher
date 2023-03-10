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
#include "philo.h"

static size_t	ft_atoll(const char *str);
static bool		is_digit(char c);
static void		parse_error(void);

void	philo_parse(int argc, char **args, t_philo_s_data *s_data)
{
	if (argc < 5 || argc > 6)
	{
		errno = EINVAL;
		return ;
	}
	s_data->philo_total = ft_atoll(args[1]);
	if (errno)
		return (parse_error());
	s_data->time_to_die = ft_atoll(args[2]);
	if (errno)
		return (parse_error());
	s_data->time_to_eat = ft_atoll(args[3]);
	if (errno)
		return (parse_error());
	s_data->time_to_sleep = ft_atoll(args[4]);
	if (errno)
		return (parse_error());
	if (argc == 5)
	{
		s_data->max_meal = -1;
		return ;
	}
	s_data->max_meal = (ssize_t) ft_atoll(args[5]);
	if (errno)
		return (parse_error());
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
		str++;
	}
	return (nb);
}

static bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static void	parse_error(void)
{
	write(2, "Parsing error\n", 14);
}
