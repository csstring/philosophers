/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:20:13 by schoe             #+#    #+#             */
/*   Updated: 2022/06/26 16:36:17 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo_bonus.h"
#include <stdlib.h>
#include <string.h>

int	ft_proc_init(t_proc *proc, char **av)
{
	int	i;

	i = 0;
	proc->number = ft_atoi(av[1]);
	proc->pid = (pid_t *)malloc(sizeof(pid_t) * proc->number);
	proc->philo = (t_philo *)malloc(sizeof(t_philo) * proc->number);
	if (proc->philo == NULL || proc->pid == NULL)
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
		proc->philo[i].eat = ft_atoi(av[3]);
		proc->philo[i].sleep = ft_atoi(av[4]);
		proc->philo[i].fork = proc->fork;
		proc->philo[i++].print = proc->print;
	}
	return (1);
}

int	ft_destroy_tool(t_proc *proc)
{
	if (sem_unlink("/fork") != 0 || sem_unlink("/print") != 0)
		return (0);
	if (sem_close(proc->fork) != 0 || sem_close(proc->print) != 0)
		return (0);
	return (1);
}

int	ft_digit_check(char **av)
{
	int	i;
	int	k;

	i = 1;
	while (av[i])
	{
		k = 0;
		if (av[i][0] == 0)
			return (0);
		while (av[i][k])
		{
			if (ft_isdigit(av[i][k]) != 1)
				return (0);
			k++;
		}
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_proc	proc;

	if (ac < 5 || ac > 6)
	{
		printf("error\n");
		return (0);
	}
	memset(&proc, 0, sizeof(proc));
	if (ft_digit_check(av) && \
			ft_proc_init(&proc, av) && \
			ft_make_philo(&proc, av, ac) && \
			ft_simul_start(&proc) && \
			ft_destroy_tool(&proc))
		return (0);
	printf("error\n");
	return (0);
}
