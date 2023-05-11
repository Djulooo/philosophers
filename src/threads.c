/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 01:02:27 by juleslaisne       #+#    #+#             */
/*   Updated: 2023/05/11 15:24:36 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	mutex_lock(t_philo *data)
{
	data->state = THINKING;
	if (pthread_mutex_lock(&(data->p_right->mutex)) == 1)
		return (1);
	print_philo_state(data, "has taken a fork");
	if (pthread_mutex_lock(&(data->mutex)) == -1)
		return (1);
	print_philo_state(data, "has taken a fork");
	data->state = EATING;
	print_philo_state(data, "is eating");
	usleep(data->n_time_to_eat * 1000);
	pthread_mutex_unlock(&(data->p_right->mutex));
	pthread_mutex_unlock(&(data->mutex));
	print_philo_state(data, "is sleeping");
	data->state = SLEEPING;
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
	meals = data->n_eat;
	while (data->state != FULL)
	{
		if (data->stop == 1)
			return (NULL);
		if (mutex_lock(data) == 1)
			return (NULL);
		if (meals > 0)
			meals--;
		if (meals == 0)
			data->state = FULL;
		printf("philo[%d] has %d meals left\n", data->id, meals);
	}
	return (NULL);
}

int	thread_join_destroy(int n_threads, t_philo *philo, pthread_t threads[])
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
	i = 0;
	while (i < n_threads)
	{
		pthread_mutex_destroy(&philo->mutex);
		i++;
	}
	return (0);
}
