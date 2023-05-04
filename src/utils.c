/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:22:02 by jlaisne           #+#    #+#             */
/*   Updated: 2023/05/04 16:21:50 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;
	char			*str;

	i = 0;
	str = s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	if (size > 0 && count > SIZE_MAX / size)
		return (NULL);
	mem = (void *)malloc(count * size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, (count * size));
	return (mem);
}

void	free_philo(t_philo *philo, pthread_t *threads)
{
	if (philo)
		free(philo);
	if (threads)
		free(threads);
}

void	usleep_fraction(int	time)
{
	int	res;
	int	mod;
	int	index;

	index = 0;
	res = time / 50;
	mod = time % 50;
	while (index < res)
	{
		usleep(50);
		index++;
	}
	if (mod != 0)
		usleep(mod);
}

void	print_philo_state(t_philo *philo, char *state)
{
	time_t timestamp;

    timestamp = philo->time.tv_sec;
	long long epoch_time_ms = (long long)timestamp * 1000 + philo->time.tv_sec / 1000 - EPOCH_TIME_MS;
	printf("%lldms philo %d %s\n", epoch_time_ms, philo->id, state);
}