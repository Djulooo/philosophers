/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 01:02:27 by juleslaisne       #+#    #+#             */
/*   Updated: 2023/05/15 15:38:21 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	mutex_lock(t_philo *data)
{
	data->state = THINKING;
	if (data->id == 1 && data->stop != 1)
	{
		if (pthread_mutex_lock(&(data->mutex)) == -1)
			return (1);
		if (print_philo_state(data, "has taken a fork") == 1)
			return (1);
		if (pthread_mutex_lock(&(data->p_right->mutex)) == 1)
			return (1);
		if (print_philo_state(data, "has taken a fork") == 1)
			return (1);
	}
	else if (data->id != 1 && data->stop != 1)
	{
		if (pthread_mutex_lock(&(data->p_right->mutex)) == 1)
			return (1);
		if (print_philo_state(data, "has taken a fork") == 1)
			return (1);
		if (pthread_mutex_lock(&(data->mutex)) == -1)
			return (1);
		if (print_philo_state(data, "has taken a fork") == 1)
			return (1);
	}
	return (0);
}

static int	mutex_eat_unlock(t_philo *data)
{
	data->state = EATING;
	if (print_philo_state(data, "is eating") == 1)
		return (1);
	ft_usleep(data->n_time_to_eat, data);
	data->state = SLEEPING;
	if (print_philo_state(data, "is sleeping") == 1)
		return (1);
	if (data->id == 1 && data->stop != 1)
	{
		pthread_mutex_unlock(&(data->mutex));
		pthread_mutex_unlock(&(data->p_right->mutex));
	}
	else if (data->id != 1 && data->stop != 1)
	{
		pthread_mutex_unlock(&(data->p_right->mutex));
		pthread_mutex_unlock(&(data->mutex));
	}
	ft_usleep(data->n_time_to_sleep, data);
	data->state = THINKING;
	if (print_philo_state(data, "is thinking") == 1)
		return (1);
	return (0);
}

void	*thread_func(void *arg)
{
	t_philo	*data;
	int		meals;

	data = (t_philo *)arg;
	if (data->id % 2 == 1)
		ft_usleep(data->n_time_to_eat, data);
	meals = data->n_eat;
	while (data->stop != 1 && data->state != FULL)
	{
		if (data->stop == 1)
			break ;
		if (data->stop != 1 && mutex_lock(data) == 1)
			return (NULL);
		if (data->stop != 1 && mutex_eat_unlock(data) == 1)
			return (NULL);
		if (meals > 0)
			meals--;
		if (meals == 0)
			data->state = FULL;
	}
	return (NULL);
}
