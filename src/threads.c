/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 01:02:27 by juleslaisne       #+#    #+#             */
/*   Updated: 2023/05/04 16:12:35 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_lock_forks(t_philo *data)
{
	if (data->p_left->fork == AVAILABLE && data->fork == AVAILABLE)
	{
		data->p_left->fork = UNAVAILABLE;
		data->fork = UNAVAILABLE;
		print_philo_state(data, "has taken a fork");
		pthread_mutex_lock(&(data->mutex));
		pthread_mutex_lock(&(data->p_left->mutex));
		print_philo_state(data, "is eating");
		usleep_fraction(data->n_time_to_eat);
		pthread_mutex_unlock(&(data->mutex));
		pthread_mutex_unlock(&(data->p_left->mutex));
		data->time.tv_sec += data->n_time_to_eat;
	}
	data->p_left->fork = AVAILABLE;
	data->fork = AVAILABLE;
}

void	*thread_func(void *arg)
{
	t_philo	*data;

	data = (t_philo *)arg;
	while (1)
		mutex_lock_forks(data);
	return (NULL);
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
