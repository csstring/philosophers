/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:21:29 by schoe             #+#    #+#             */
/*   Updated: 2022/06/25 20:54:24 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"
int	ft_max_count_check(t_philo *philo)
{
	ssize_t time;

	if (philo->eat_count < philo->max_count)
		return (0);
	sem_wait(philo->print);
	philo->die_check = 1;
	time = ft_get_usec();
	printf("%ld all philo eat %d times\n", time - philo->make, \
			philo->max_count);
	//sem_post(proc->print);
	return (1);
}

int	ft_hungry_check(t_philo *philo)
{	
	ssize_t time;

	time = ft_get_usec();
	if (philo->end_eat == 0 && time - philo->make > (ssize_t)philo->die)
	{
		sem_wait(philo->print);
		philo->die_check = 1;
		time = ft_get_usec();
		printf("%ld %d died\n", time - philo->make, philo->name);
		//sem_post(proc->print);
		return (1);
	}
	else if (philo->end_eat != 0 && time - philo->end_eat > (ssize_t)philo->die)
	{
		sem_wait(philo->print);
		philo->die_check = 1;
		time = ft_get_usec();
		printf("%ld %d died\n", time - philo->make, philo->name);
		//sem_post(proc->print);
		return (1);
	}
	return (0);
}

void	*ft_view_philo(void *input)
{
	int	i;
	t_philo *philo;

	philo = (t_philo *)input;
	i = 0;
	while (1)
	{
		if (ft_hungry_check(philo))
			break ;
		if (philo->max_count)
		{
			if (ft_max_count_check(philo))
				break;
		}
	}
	kill(philo->pid, 3);
	return (0);
}

int	ft_proc_init(t_proc *proc, char **av)
{
	int	i;

	i = 0;
	proc->number = ft_atoi(av[1]);
//	proc->fork = (sem_t *)malloc(sizeof(sem_t) * 1);
//	proc->print = (sem_t *)malloc(sizeof(sem_t) * 1);
	proc->pid = (pid_t *)malloc(sizeof(pid_t) * proc->number);
	proc->philo = (t_philo *)malloc(sizeof(t_philo) * proc->number);
	if (proc->fork == NULL || proc->print == NULL || proc->philo == NULL)
		return (0);
	sem_unlink("/fork");
	sem_unlink("/print");
	proc->fork = sem_open("/fork", O_CREAT | O_EXCL, 0644, proc->number); 
	proc->print = sem_open("/print", O_CREAT | O_EXCL, 0644, 1); 
	return (1);
}

int	ft_make_philo(t_proc *proc, char **av, int ac)
{
	int	i;
	pid_t	pid;

	i = 0;
	while (i < proc->number)
	{
		if (ac == 6)
			proc->philo[i].max_count = ft_atoi(av[5]);
		else
			proc->philo[i].max_count = 0;
		proc->philo[i].die = ft_atoi(av[2]);
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
			ft_philo_simul((void *)&proc->philo[i]);
			break;
		}
		kill(pid, 17);
		proc->philo[(i + 1) % proc->number].pid = pid;
		proc->pid[(i + 1) % proc->number] = pid;
		i++;
	}
	if (pid != 0)
		kill(0, 19);
	waitpid(0, &i ,0);
	i = 0;
	while (i < proc->number)
		kill(proc->pid[i++], 9);
	return (1);
}
