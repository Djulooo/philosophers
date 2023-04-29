/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:22:02 by jlaisne           #+#    #+#             */
/*   Updated: 2023/04/29 15:53:14 by jlaisne          ###   ########.fr       */
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
