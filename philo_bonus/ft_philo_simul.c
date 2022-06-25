/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_simul.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:16:03 by schoe             #+#    #+#             */
/*   Updated: 2022/06/25 20:41:33 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int	ft_put_sem(t_philo *philo)
{
//	sem_post(philo->print);
	sem_post(philo->fork);
	sem_post(philo->fork);
	return (1);
}

int	ft_sleep_think(t_philo *philo)
{
	sem_wait(philo->print);
//	if (philo->die_check == 1)
//		return (ft_put_sem(philo));
	printf("%ld %d is sleeping\n",(ft_get_usec() - philo->make), philo->name);
	sem_post(philo->print);
	ft_msleep(philo->sleep);
	sem_wait(philo->print);
//	if (philo->die_check == 1)
//		return (ft_put_sem(philo));
	printf("%ld %d is thinking\n",(ft_get_usec() - philo->make), philo->name);
	sem_post(philo->print);
	return (0);
}

int	ft_even_eat(t_philo *philo)
{
	sem_wait(philo->fork);
	sem_wait(philo->fork);
//	if (philo->die_check == 1)
//		return (ft_put_sem(philo));
	sem_wait(philo->print);
//	if (philo->die_check == 1)
//		return (ft_put_sem(philo));
	philo->end_eat = ft_get_usec();
	printf("%ld %d is eating\n", philo->end_eat - philo->make, philo->name);
	sem_post(philo->print);
	philo->eat_count++;
	ft_msleep(philo->eat);
	sem_post(philo->fork);
	sem_post(philo->fork);
	return (0);
}

void	*ft_philo_simul(void *input)
{
	t_philo *philo;
	pthread_t	tid;

	philo = (t_philo *)input;
	pthread_create(&tid , NULL, ft_view_philo, (void *)philo);
	philo->make = ft_get_usec();
	pthread_detach(tid);
	if (philo->name % 2 == 1)
		usleep(50);
	while (philo->die_check != 1)
	{
		if (ft_even_eat(philo) || ft_sleep_think(philo))
			break ;
		//usleep(1000);
	}
	return (0);
}
