/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juleslaisne <juleslaisne@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 00:33:29 by juleslaisne       #+#    #+#             */
/*   Updated: 2023/04/29 01:31:51 by juleslaisne      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_struct(t_philo *philo)
{
	philo->thread = NULL;
	philo->thread_arg = NULL;
	philo->thread_arg = malloc(sizeof(int) * philo->n_philo);
	if (!philo->thread_arg)
		return (printf("Malloc error for thread_arg"), 1);
	philo->thread = malloc(philo->n_philo * sizeof(pthread_t));
	if (!philo->thread)
		return (printf("Malloc error for thread_arg"), 1);
	return (0);
}

t_philo  *init_arguments(int argc, char **argv, t_philo *philo)
{
	philo = malloc(sizeof(t_philo *));
	philo->n_eat = -2;
	philo->n_time_to_die = -1; //ft_atoi(argv[2], "time_to_die");
	philo->n_time_to_eat = ft_atoi(argv[3], "time_to_eat");
	philo->n_time_to_sleep = ft_atoi(argv[4], "time_to_sleep");
	if (gettimeofday(&philo->time, NULL) == -1)
        return (printf("Error getting time of day\n"), NULL);
	if (argc == 6)
		philo->n_eat = ft_atoi(argv[5], "number_of_times_each_philosopher_must_eat");
	if (philo->n_time_to_die == -1 || philo->n_time_to_eat == -1 
		|| philo->n_time_to_sleep == -1 || philo->n_eat == -1)
		return (NULL);
	return (philo);
}

int init_threads(int n_threads, int argc, char **argv)
{
	int			i;
	pthread_t	threads[n_threads];
	t_philo		philo[n_threads];
	
	if (init_struct(philo) == 1)
		return (free_philo(philo), 1);
	i = 0;
	while (i < n_threads) 
	{
		philo[i].id = i + 1;
		philo[i] = *init_arguments(argc, argv, &philo[i]);
		if (init_arguments(argc, argv, &philo[i]) == NULL)
			return (free_philo(philo), 1);
		if (pthread_create(&threads[i], NULL, thread_handler, (void*)&philo[i])) 
		{
			printf("Error creating thread\n");
			return (free_philo(philo), 1);
		}
		i++;
	}
	if (thread_join(n_threads, threads) == 1)
		return (free_philo(philo), 1);
	return (0);
}

int main(int argc, char **argv) 
{
	int n_threads;
	
	if (argc == 5 || argc == 6)
	{
		n_threads = ft_atoi(argv[1], "number_of_philosophers");
		if (n_threads <= 0)
			return (printf("We need at least one philosopher so he can die alone\n"), 1);
		if (init_threads(n_threads, argc, argv) == 1)
			return (1);
	}
	return (0);
}
