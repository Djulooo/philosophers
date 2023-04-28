#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	struct timeval	time;
	pthread_t		*thread;
	int				*thread_arg;
	int				id;
	int				n_philo;
	int				n_time_to_die;
	int				n_time_to_eat;
	int				n_time_to_sleep;
	int				n_eat;
}	t_philo;

int		ft_atoi(const char *str, char *arg);
void	free_philo(t_philo *philo);

int 	thread_join(int n_threads, pthread_t threads[]);
void	*thread_handler(void *arg);

#endif