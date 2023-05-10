/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:21:59 by jlaisne           #+#    #+#             */
/*   Updated: 2023/05/10 14:08:44 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdint.h>

typedef enum s_state {
	EATING,
	SLEEPING,
	THINKING,
	FULL,
	STARVED
}	t_state;

typedef struct s_philo
{
	struct timeval	time_start;
	struct timeval	time_end;
	struct s_philo	*p_right;
	pthread_mutex_t	mutex;
	t_state			state;
	long			epoch_time_ms;
	int				n_time_to_die;
	int				n_time_to_eat;
	int				n_time_to_sleep;
	int				n_eat;
	int				id;
}	t_philo;

int		ft_atoi(const char *str, char *arg);
void	free_philo(t_philo *philo, pthread_t *threads);
void	*ft_calloc(size_t count, size_t size);
long	get_time(t_philo *philo);

int		thread_join_destroy(int n_threads, t_philo *philo, pthread_t threads[]);
void	*thread_func(void *arg);
void	place_at_table(t_philo *philo, int n_threads);
void	print_philo_state(t_philo *philo, char *state);

#endif