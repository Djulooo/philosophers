#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>

typedef struct s_philo
{
	int	n_philo;
	int	n_time_to_die;
	int	n_time_to_eat;
	int	n_time_to_sleep;
	int	n_eat;
}	t_philo;

int	ft_atoi(const char *str, char *arg);

#endif