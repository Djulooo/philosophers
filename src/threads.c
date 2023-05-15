/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 01:02:27 by juleslaisne       #+#    #+#             */
/*   Updated: 2023/05/15 14:17:09 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	mutex_lock(t_philo *data)
{
	data->state = THINKING;
	if (pthread_mutex_lock(&(data->mutex)) == -1)
		return (1);
	print_philo_state(data, "has taken a fork");
	if (pthread_mutex_lock(&(data->p_right->mutex)) == 1)
		return (1);
	print_philo_state(data, "has taken a fork");
	data->state = EATING;
	print_philo_state(data, "is eating");
	usleep(data->n_time_to_eat * 1000);
	data->state = SLEEPING;
	print_philo_state(data, "is sleeping");
	pthread_mutex_unlock(&(data->mutex));
	pthread_mutex_unlock(&(data->p_right->mutex));
	usleep(data->n_time_to_sleep * 1000);
	data->state = THINKING;
	print_philo_state(data, "is thinking");
	return (0);
}

void	*thread_func(void *arg)
{
	t_philo	*data;
	int		meals;

	data = (t_philo *)arg;
	if (data->id % 2 == 1)
		usleep(data->n_time_to_eat * 1000);
	meals = data->n_eat;
	while (data->state != FULL)
	{
		if (data->stop == 1)
			break ;
		if (mutex_lock(data) == 1)
			return (NULL);
		if (meals > 0)
			meals--;
		if (meals == 0)
			data->state = FULL;
	}
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
	return (1);
}
