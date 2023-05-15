/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:21:59 by jlaisne           #+#    #+#             */
/*   Updated: 2023/05/15 12:38:12 by jlaisne          ###   ########.fr       */
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
# include "typedef.h"

int		ft_atoi(const char *str, char *arg);
void	free_philo(t_philo *philo, pthread_t *threads);
void	*ft_calloc(size_t count, size_t size);
long	get_time(t_philo *philo);

int		thread_join(int n_threads, pthread_t threads[]);
int		mutex_destroy(int n_threads, t_philo *philo);
void	*thread_func(void *arg);
void	place_at_table(t_philo *philo, int n_threads);
void	print_philo_state(t_philo *philo, char *state);
int		check_death(t_philo *philo, int n_threads);

#endif