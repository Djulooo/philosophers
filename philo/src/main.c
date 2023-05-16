/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 00:33:29 by juleslaisne       #+#    #+#             */
/*   Updated: 2023/05/16 13:05:47 by jlaisne          ###   ########.fr       */
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
			philo[i].p_right = &philo[n_threads - 1];
		else
			philo[i].p_right = &philo[i - 1];
		i++;
	}
	philo->n_philo = n_threads;
}

static t_philo	*init_arguments(int argc, char **argv, t_philo *philo)
{
	philo->stop = 0;
	philo->n_eat = -2;
	philo->n_time_to_die = ft_atoi(argv[2], "time_to_die");
	philo->n_time_to_eat = ft_atoi(argv[3], "time_to_eat");
	philo->n_time_to_sleep = ft_atoi(argv[4], "time_to_sleep");
	if (argc == 6)
		philo->n_eat = ft_atoi(argv[5], \
			"number_of_times_each_philosopher_must_eat");
	if (philo->n_time_to_die == -1 || philo->n_time_to_eat == -1 \
		|| philo->n_time_to_sleep == -1 || philo->n_eat == -1)
		return (NULL);
	if (gettimeofday(&philo->time_start, NULL) == -1)
		return (NULL);
	philo->epoch_time_ms = (philo->time_start.tv_sec * 1000) \
		+ (philo->time_start.tv_usec / 1000);
	philo->last_meal_time = get_time(philo) - philo->epoch_time_ms;
	return (philo);
}

static int	init_struct(int argc, char **argv, int n_threads, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < n_threads)
	{
		philo[i].id = i + 1;
		if (pthread_mutex_init(&philo->mutex, NULL) != 0)
			return (1);
		if (init_arguments(argc, argv, &philo[i]) == NULL)
			return (1);
		i++;
	}
	if (n_threads > 1)
		place_at_table(philo, n_threads);
	else
		philo[0].p_right = &philo[0];
	if (pthread_mutex_init(&philo->write_mutex, NULL) != 0)
		return (1);
	return (0);
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
	if (init_struct(argc, argv, n_threads, philo) == 1)
		return (free_philo(philo, threads), 1);
	i = 0;
	while (i < n_threads)
	{
		if (pthread_create(&threads[i], NULL, thread_func, (void *)&philo[i]))
			return (printf("Error pthread\n"), free_philo(philo, threads), 1);
		i++;
	}
	if (check_death(philo, n_threads) == 1)
		return (thread_join(n_threads, threads), \
			mutex_destroy(n_threads, philo), free_philo(philo, threads), 1);
	if (thread_join(n_threads, threads) == 1)
		return (mutex_destroy(n_threads, philo), free_philo(philo, threads), 1);
	return (mutex_destroy(n_threads, philo), free_philo(philo, threads), 0);
}

int	main(int argc, char **argv)
{
	int	n_threads;

	if (argc == 5 || argc == 6)
	{
		n_threads = ft_atoi(argv[1], "number_of_philosophers");
		if (n_threads <= 0)
			return (printf("Invalid number of philosophers.\n"), 1);
		if (init_threads(n_threads, argc, argv) == 1)
			return (1);
		return (0);
	}
	return (printf("Invalid arguments."), 1);
}
