/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dead.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:07:06 by jlaisne           #+#    #+#             */
/*   Updated: 2023/05/15 18:00:35 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_state(t_philo *philo, int n_threads, int i, int full)
{
	while (i < n_threads)
	{
		if (philo[i].state == FULL)
			full++;
		if (full == n_threads)
			return (1);
		if ((get_time(philo) - philo->epoch_time_ms) - (philo[i].last_meal_time) > philo->n_time_to_die)
		{
			philo[i].state = STARVED;
			if (print_philo_state(&philo[i], "has died") == 1)
				return (1);
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
	return (0);
}

int	check_death(t_philo *philo, int n_threads)
{
	int	i;
	int	full;

	while (1)
	{
		i = 0;
		full = 0;
		if (check_state(philo, n_threads, i, full) == 1)
			return (1);
		usleep(50);
	}
	return (0);
}

int	thread_join(int n_threads, pthread_t threads[])
{
	int	i;

	i = 0;
	while (i < n_threads)
	{
		if (pthread_join(threads[i], NULL))
		{
			printf("Error joining thread\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	mutex_destroy(int n_threads, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < n_threads)
	{
		if (pthread_mutex_destroy(&philo->mutex) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_destroy(&philo->write_mutex) != 0)
		return (0);
	return (1);
}
