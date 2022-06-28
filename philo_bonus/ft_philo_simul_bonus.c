/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_simul_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:16:03 by schoe             #+#    #+#             */
/*   Updated: 2022/06/26 14:53:15 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <sys/wait.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

void	ft_sleep_think(t_philo *philo)
{
	sem_wait(philo->print);
	printf("%ld %d is sleeping\n", (ft_get_usec() - philo->make), philo->name);
	sem_post(philo->print);
	ft_msleep(philo->sleep);
	sem_wait(philo->print);
	printf("%ld %d is thinking\n", (ft_get_usec() - philo->make), philo->name);
	sem_post(philo->print);
}

void	ft_eat(t_philo *philo)
{
	sem_wait(philo->fork);
	sem_wait(philo->print);
	printf("%ld %d has taken a fork\n", \
			(ft_get_usec() - philo->make), philo->name);
	sem_post(philo->print);
	sem_wait(philo->fork);
	sem_wait(philo->print);
	philo->end_eat = ft_get_usec();
	printf("%ld %d has taken a fork\n%ld %d is eating\n", \
			philo->end_eat - philo->make, philo->name, \
			philo->end_eat - philo->make, philo->name);
	sem_post(philo->print);
	philo->eat_count++;
	ft_msleep(philo->eat);
	sem_post(philo->fork);
	sem_post(philo->fork);
}

void	ft_philo_simul(void *input)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)input;
	pthread_create(&tid, NULL, ft_view_philo, (void *)philo);
	philo->make = ft_get_usec();
	pthread_detach(tid);
	if (philo->name % 2 == 1)
		usleep(200);
	while (1)
	{
		ft_eat(philo);
		ft_sleep_think(philo);
	}
}

int	ft_simul_start(t_proc *proc)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < proc->number)
	{
		pid = fork();
		if (pid == -1)
			return (0);
		else if (pid == 0)
		{
			ft_philo_simul((void *)&proc->philo[i]);
			break ;
		}
		proc->pid[i] = pid;
		kill(pid, 17);
		i++;
	}
	if (pid != 0)
		kill(0, 19);
	waitpid(0, &i, 0);
	i = 0;
	while (i < proc->number)
		kill(proc->pid[i++], 9);
	return (1);
}
