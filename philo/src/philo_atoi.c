/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:22:29 by jlaisne           #+#    #+#             */
/*   Updated: 2023/05/15 12:50:08 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_isspace(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t'
		|| str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	return (i);
}

static int	handle_sign(char a, char b, int *i)
{
	if (a == '+' && (b >= '0' && b <= '9'))
		(*i)++;
	return (1);
}

static int	check_max_int(long nb)
{
	if (nb > 2147483647)
		return (1);
	return (0);
}

int	ft_atoi(const char *str, char *arg)
{
	int		i;
	long	nb;
	int		sign;

	i = check_isspace(str);
	nb = 0;
	sign = 1;
	if (str[i + 1])
		sign = handle_sign(str[i], str[i + 1], &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (check_max_int(nb) == 1)
			break ;
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
	{
		printf("Invalid integer format for argument: %s\n", arg);
		return (-1);
	}
	return (nb * sign);
}
