/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:10:17 by jlaisne           #+#    #+#             */
/*   Updated: 2023/05/16 14:48:15 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t count, size_t size)
{
	void			*mem;
	unsigned int	i;
	char			*str;

	if (size > 0 && count > SIZE_MAX / size)
		return (NULL);
	mem = (void *)malloc(count * size);
	if (!mem)
		return (NULL);
	i = 0;
	str = mem;
	while (i < (count * size))
	{
		str[i] = '\0';
		i++;
	}
	return (mem);
}

void	ft_usleep(long time, t_philo *philo)
{
	long	start;

	start = get_time(philo);
	while (get_time(philo) - start < time)
		usleep(100);
}

void	free_philo(t_philo *philo, pthread_t *threads)
{
	if (philo)
		free(philo);
	if (threads)
		free(threads);
}

long	get_time(t_philo *philo)
{
	long	time;

	if (gettimeofday(&philo->time_end, NULL) == -1)
		return (-1);
	time = (philo->time_end.tv_sec * 1000) + (philo->time_end.tv_usec / 1000);
	return (time);
}

int	print_philo_state(t_philo *philo, char *state)
{
	long	time;

	time = get_time(philo);
	if (time == -1)
		return (1);
	if (philo->state == EATING)
		philo->last_meal_time = time - philo->epoch_time_ms;
	if (pthread_mutex_lock(&(philo->write_mutex)) == -1)
		return (1);
	if (philo->stop != 1)
		printf("%ldms philo %d %s\n", time - philo->epoch_time_ms, \
			philo->id, state);
	if (pthread_mutex_unlock(&(philo->write_mutex)) == -1)
		return (1);
	return (0);
}
