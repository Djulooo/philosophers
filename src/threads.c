/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juleslaisne <juleslaisne@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 01:02:27 by juleslaisne       #+#    #+#             */
/*   Updated: 2023/04/29 01:33:28 by juleslaisne      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_handler(void *arg) 
{
	t_philo*	data;
	
	if (arg)
	{
		data = (t_philo*)arg;
		printf("%ld.%06dms Thread %d\n", data->time.tv_sec, data->time.tv_usec, data->id);
	}
	return (NULL);
}

int thread_join(int n_threads, pthread_t threads[])
{
	int i;

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
