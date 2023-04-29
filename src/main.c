/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 00:33:29 by juleslaisne       #+#    #+#             */
/*   Updated: 2023/04/29 16:10:24 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	place_at_table(t_philo *philo, int n_threads)
{
	int	i;

	i = 0;
	while (i < n_threads)
	{
		if (i == 0)
		{
			philo[i].p_left = &philo[i + 1];
			philo[i].p_left = &philo[n_threads];
		}
		else if (i == n_threads - 1)
		{
			philo[i].p_left = &philo[1];
			philo[i].p_left = &philo[i - 1];
		}
		else
		{
			philo[i].p_left = &philo[i + 1];
			philo[i].p_left = &philo[i - 1];
		}
		i++;
	}
}

static t_philo	*init_arguments(int argc, char **argv, t_philo *philo)
{
	philo->n_eat = -2;
	philo->n_time_to_die = ft_atoi(argv[2], "time_to_die");
	philo->n_time_to_eat = ft_atoi(argv[3], "time_to_eat");
	philo->n_time_to_sleep = ft_atoi(argv[4], "time_to_sleep");
	if (gettimeofday(&philo->time, NULL) == -1)
		return (printf("Error getting time of day\n"), NULL);
	if (argc == 6)
		philo->n_eat = ft_atoi(argv[5], \
			"number_of_times_each_philosopher_must_eat");
	if (philo->n_time_to_die == -1 || philo->n_time_to_eat == -1 \
		|| philo->n_time_to_sleep == -1 || philo->n_eat == -1)
		return (NULL);
	return (philo);
}

static int	init_threads(int n_threads, int argc, char **argv)
{
	int			i;
	pthread_t	*threads;
	t_philo		*philo;

	threads = malloc(sizeof(pthread_t) * n_threads);
	if (!threads)
		return (1);
	philo = ft_calloc(n_threads, sizeof(t_philo));
	if (!philo)
		return (free_philo(philo, threads), 1);
	i = 0;
	while (i < n_threads)
	{
		philo[i].id = i + 1;
		place_at_table(&philo[i], n_threads);
		if (init_arguments(argc, argv, &philo[i]) == NULL)
			return (free_philo(philo, threads), 1);
		if (pthread_create(&threads[i], NULL, thread_func, (void *)&philo[i]))
			return (printf("Error pthread\n"), free_philo(philo, threads), 1);
		i++;
	}
	if (thread_join(n_threads, threads) == 1)
		return (free_philo(philo, threads), 1);
	return (free_philo(philo, threads), 0);
}

int	main(int argc, char **argv)
{
	int	n_threads;

	if (argc == 5 || argc == 6)
	{
		n_threads = ft_atoi(argv[1], "number_of_philosophers");
		if (n_threads <= 0)
			return (printf("We need at least one philosopher so he \
				can die alone\n"), 1);
		if (init_threads(n_threads, argc, argv) == 1)
			return (1);
		return (0);
	}
	return (printf("Invalid arguments, needed: number_of_philosophers, time_to_die, \
		time_to_eat, time_to_sleep, \
			[number_of_times_each_philosopher_must_eat]"), 1);
}
