#include "philo.h"

void	free_philo(t_philo *philo)
{
	if (philo->thread)
		free(philo->thread);
	if (philo->thread_arg)
		free(philo->thread_arg);
}
