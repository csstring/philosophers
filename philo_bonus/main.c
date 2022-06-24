/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:20:13 by schoe             #+#    #+#             */
/*   Updated: 2022/06/24 21:41:55 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_destroy_tool(t_proc *proc)
{
	sem_unlink("fork");
	sem_unlink("print");
	sem_close(proc->fork);
	sem_close(proc->print);
	return (1);
}
/*
int	ft_join_thread(t_proc *proc)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	i= 0;
	while (i < proc->number)
	{
		if (pthread_join(proc->tid[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}*/

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
	if (ft_digit_check(av) && \
			ft_proc_init(&proc, av, ac) && \
			ft_make_philo(&proc, av) && \
			ft_view_philo(&proc) && \
			ft_destroy_tool(&proc))
		return (0);
	printf("error\n");
	return (0);
}
