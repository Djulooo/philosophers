/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dead.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:07:06 by jlaisne           #+#    #+#             */
/*   Updated: 2023/05/11 15:22:48 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo, int n_threads)
{
	int	i;

	i = 0;
	while (1)
	{
		i = 0;
		while (i < n_threads)
		{
			if ((get_time(philo) - philo->epoch_time_ms) - (philo[i].last_meal_time) > philo->n_time_to_die)
			{
				philo[i].state = STARVED;
				print_philo_state(&philo[i], "has died");
				i = 0;
				while (i < n_threads)
				{
					philo[i].stop = 1;
					i++;
				}
				return (1);
			}
			i++;
		}
		usleep(100);
	}
	return (1);
}
