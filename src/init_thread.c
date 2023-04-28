#include "philo.h"


static void	*thread_function(void *arg)
{
	int id;

	id = *(int *)arg;
	printf("thread id [%d] is running\n", id);
	return (NULL);
}

int	thread_join(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->n_philo)
	{
		if (pthread_join(philo->thread[i], NULL) > 0)
			return (printf("pthread_join failed"), 1);
		i++;
	}
	return (0);
}

int	init_thread(t_philo *philo)
{
	int			i;

	i = 0;
	while (i < philo->n_philo)
	{
		philo->thread_arg[i] = i + 1;
		if (pthread_create(&philo->thread[i], NULL, thread_function, &philo->thread_arg[i]) > 0)
			return (printf("pthread_create failed"), 1);
		i++;
	}
	if (thread_join(philo) == 1)
		return (1);
	return (0);
}
