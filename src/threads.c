/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 01:02:27 by juleslaisne       #+#    #+#             */
/*   Updated: 2023/04/29 16:07:20 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_func(void *arg)
{
	t_philo	*data;

	data = (t_philo *)arg;
	printf("%ld.%06ldms Thread %d\n", \
		data->time.tv_sec, data->time.tv_usec, data->id);
	// printf("philo: %d\n", data->p_right->id);
	// printf("philo: %d\n", data->p_left->id);
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
