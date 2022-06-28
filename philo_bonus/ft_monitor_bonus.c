/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitor_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 13:37:38 by schoe             #+#    #+#             */
/*   Updated: 2022/06/26 14:54:28 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdlib.h>

int	ft_max_count_check(t_philo *philo)
{
	ssize_t	time;

	if (philo->eat_count < philo->max_count)
		return (0);
	sem_wait(philo->print);
	time = ft_get_usec();
	printf("%ld all philo eat %d times\n", time - philo->make, \
			philo->max_count);
	return (1);
}

int	ft_hungry_check(t_philo *philo)
{
	ssize_t	time;

	time = ft_get_usec();
	if (philo->end_eat == 0 && time - philo->make > (ssize_t)philo->die)
	{
		sem_wait(philo->print);
		time = ft_get_usec();
		printf("%ld %d died\n", time - philo->make, philo->name);
		return (1);
	}
	else if (philo->end_eat != 0 && time - philo->end_eat > (ssize_t)philo->die)
	{
		sem_wait(philo->print);
		time = ft_get_usec();
		printf("%ld %d died\n", time - philo->make, philo->name);
		return (1);
	}
	return (0);
}

void	*ft_view_philo(void *input)
{
	t_philo	*philo;

	philo = (t_philo *)input;
	while (1)
	{
		if (ft_hungry_check(philo))
			break ;
		if (philo->max_count)
		{
			if (ft_max_count_check(philo))
				break ;
		}
	}
	exit(1);
}
