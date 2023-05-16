/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:13:12 by jlaisne           #+#    #+#             */
/*   Updated: 2023/05/15 18:04:47 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# include "philo.h"

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
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	death_mutex;
	t_state			state;
	long			epoch_time_ms;
	long			last_meal_time;
	int				n_time_to_die;
	int				n_time_to_eat;
	int				n_time_to_sleep;
	int				n_eat;
	int				id;
	int				stop;
	int				n_philo;
}	t_philo;

#endif