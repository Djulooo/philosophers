/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:13:12 by jlaisne           #+#    #+#             */
/*   Updated: 2023/05/03 14:14:43 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# include "philo.h"

typedef enum s_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_philo
{
	struct timeval	time;
	struct s_philo	*p_left;
	struct s_philo	*p_right;
	int				id;
	int				n_time_to_die;
	int				n_time_to_eat;
	int				n_time_to_sleep;
	int				n_eat;
}	t_philo;

#endif