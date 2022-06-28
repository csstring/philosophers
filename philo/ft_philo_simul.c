/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_simul.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:16:03 by schoe             #+#    #+#             */
/*   Updated: 2022/06/26 16:15:13 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	ft_put_mutex(t_philo *philo)
{
	pthread_mutex_unlock(philo->print);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	return (1);
}

int	ft_sleep_think(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	if (philo->die_check == 1)
		return (ft_put_mutex(philo));
	printf("%ld %d is sleeping\n", (ft_get_usec() - philo->make), philo->name);
	pthread_mutex_unlock(philo->print);
	ft_msleep(philo->sleep);
	pthread_mutex_lock(philo->print);
	if (philo->die_check == 1)
		return (ft_put_mutex(philo));
	printf("%ld %d is thinking\n", (ft_get_usec() - philo->make), philo->name);
	pthread_mutex_unlock(philo->print);
	return (0);
}

int	ft_odd_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	pthread_mutex_lock(philo->print);
	if (philo->die_check == 1)
		return (ft_put_mutex(philo));
	printf("%ld %d has taken a fork\n", (ft_get_usec() - philo->make), \
			philo->name);
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(philo->right);
	if (philo->die_check == 1)
		return (ft_put_mutex(philo));
	pthread_mutex_lock(philo->print);
	if (philo->die_check == 1)
		return (ft_put_mutex(philo));
	philo->end_eat = ft_get_usec();
	printf("%ld %d has taken a fork\n%ld %d is eating\n", \
			philo->end_eat - philo->make, philo->name, \
			philo->end_eat - philo->make, philo->name);
	pthread_mutex_unlock(philo->print);
	philo->eat_count++;
	ft_msleep(philo->eat);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	return (0);
}

int	ft_even_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right);
	pthread_mutex_lock(philo->print);
	if (philo->die_check == 1)
		return (ft_put_mutex(philo));
	printf("%ld %d has taken a fork\n", (ft_get_usec() - philo->make), \
			philo->name);
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(philo->left);
	if (philo->die_check == 1)
		return (ft_put_mutex(philo));
	pthread_mutex_lock(philo->print);
	if (philo->die_check == 1)
		return (ft_put_mutex(philo));
	philo->end_eat = ft_get_usec();
	printf("%ld %d has taken a fork\n%ld %d is eating\n", \
			philo->end_eat - philo->make, philo->name, \
			philo->end_eat - philo->make, philo->name);
	pthread_mutex_unlock(philo->print);
	philo->eat_count++;
	ft_msleep(philo->eat);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	return (0);
}

void	*ft_philo_simul(void *input)
{
	t_philo	*philo;

	philo = (t_philo *)input;
	if (philo->name % 2 == 1)
	{
		usleep(100);
		while (philo->die_check != 1)
		{
			if (ft_odd_eat(philo) || ft_sleep_think(philo))
				return (0);
			usleep(500);
		}
	}
	else
	{
		usleep(10);
		while (philo->die_check != 1)
		{
			if (ft_even_eat(philo) || ft_sleep_think(philo))
				return (0);
			usleep(500);
		}
	}
	return (0);
}
