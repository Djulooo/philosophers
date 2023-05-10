/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:10:17 by jlaisne           #+#    #+#             */
/*   Updated: 2023/05/10 14:15:58 by jlaisne          ###   ########.fr       */
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

long	get_time(t_philo *philo)
{
	long	time;

	if (gettimeofday(&philo->time_end, NULL) == -1)
		return (-1);
	time = (philo->time_end.tv_sec * 1000) + (philo->time_end.tv_usec / 1000);
	return (time);
}

void	print_philo_state(t_philo *philo, char *state)
{
	long	time;

	time = get_time(philo);
	if (time == -1)
		return ;
	printf("%ldms philo %d %s\n", (time - philo->epoch_time_ms), philo->id, state);
}
 