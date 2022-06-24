/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:21:29 by schoe             #+#    #+#             */
/*   Updated: 2022/06/24 21:57:38 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int	ft_max_count_check(t_proc *proc)
{
	int	i;
	ssize_t time;

	i = 0;
	while (i < proc->number)
	{
		if (proc->philo[i].eat_count < proc->max_count)
			return (0);
		i++;
	}
	sem_wait(proc->print);
	ft_die_check(proc);
	time = ft_get_usec();
	printf("%ld all philo eat %d times\n", time - proc->philo[0].make, \
			proc->max_count);
	sem_post(proc->print);
	return (1);
}

int	ft_hungry_check(int	i, t_proc *proc)
{	
	ssize_t time;

	time = ft_get_usec();
	if (proc->philo[i].end_eat == 0 && time - proc->philo[i].make > \
			(ssize_t)proc->die)
	{
		sem_wait(proc->print);
		ft_die_check(proc);
		time = ft_get_usec();
		printf("%ld %d died\n", time - proc->philo[i].make, proc->philo[i].name);
		sem_post(proc->print);
		return (1);
	}
	else if (proc->philo[i].end_eat != 0 && time - proc->philo[i].end_eat > \
			(ssize_t)proc->die)
	{
		sem_wait(proc->print);
		ft_die_check(proc);
		time = ft_get_usec();
		printf("%ld %d died\n", time - proc->philo[i].make, proc->philo[i].name);
		sem_post(proc->print);
		return (1);
	}
	return (0);
}

int	ft_view_philo(t_proc *proc)
{
	int	i;

	i = 0;
	while (1)
	{
		while (i < proc->number)
		{
			if (ft_hungry_check(i, proc))
				return (1);
			i++;
		}
		if (proc->max_count)
		{
			if (ft_max_count_check(proc))
				return (1);
		}
		i = 0;
	}
	return (1);
}

int	ft_proc_init(t_proc *proc, char **av, int ac)
{
	int	i;

	i = 0;
	proc->number = ft_atoi(av[1]);
	proc->die = ft_atoi(av[2]);
	if (ac == 6)
		proc->max_count = ft_atoi(av[5]);
	else
		proc->max_count = 0;
	proc->fork = (sem_t *)malloc(sizeof(sem_t) * 1);
	proc->print = (sem_t *)malloc(sizeof(sem_t) * 1);
//	proc->tid = (pthread_t *)malloc(sizeof(pthread_t) * proc->number);
	proc->philo = (t_philo *)malloc(sizeof(t_philo) * proc->number);
	if (proc->fork == NULL || proc->print == NULL || proc->philo == NULL)
		return (0);
	proc->fork = sem_open("fork", O_CREAT | O_EXCL, 0644, proc->number); 
	proc->print = sem_open("print", O_CREAT | O_EXCL, 0644, 1); 
	return (1);
}

int	ft_make_philo(t_proc *proc, char **av)
{
	int	i;
//	ssize_t time;
	pid_t	pid;

	i = 0;
	while (i < proc->number)
	{
		proc->philo[i].name = i + 1;
		proc->philo[i].eat_count = 0;
		proc->philo[i].make = 0;
		proc->philo[i].end_eat = 0;
		proc->philo[i].die_check = 0;
		proc->philo[i].eat = ft_atoi(av[3]);
		proc->philo[i].sleep = ft_atoi(av[4]);
		proc->philo[i].fork = proc->fork;
		proc->philo[i++].print = proc->print;
	}
	i = 0;
	while (i < proc->number)
	{
		pid = fork();
		if (pid == 0)
		{
			proc->philo[i].make = ft_get_usec();
			ft_philo_simul((void *)&proc->philo[i]);
		}
		i++;
	}
	/*time = ft_get_usec();
	i = 0;
	while (i < proc->number)
		proc->philo[i++].make = time;*/
	return (1);
}
