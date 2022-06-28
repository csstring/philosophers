/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:20:13 by schoe             #+#    #+#             */
/*   Updated: 2022/06/26 16:35:32 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"
#include <string.h>

int	ft_destroy_tool(t_proc *proc)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(proc->print) != 0)
		return (0);
	while (i < proc->number)
	{
		if (pthread_mutex_destroy(&(proc->fork[i])) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_join_thread(t_proc *proc)
{
	int	i;

	i = 0;
	while (i < proc->number)
	{
		if (pthread_join(proc->tid[i], NULL) != 0)
			return (0);
		i++;
	}
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

int	ft_start_simul(t_proc *proc)
{
	int		i;
	ssize_t	time;

	i = 0;
	time = ft_get_usec();
	while (i < proc->number)
	{
		if (pthread_create(&(proc->tid[i]), NULL, ft_philo_simul, \
					(void *)&proc->philo[i]) != 0)
			return (0);
		proc->philo[i++].make = time;
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
			ft_proc_init(&proc, av, ac) && \
			ft_make_philo(&proc, av) && \
			ft_start_simul(&proc) && \
			ft_view_philo(&proc) && \
			ft_join_thread(&proc) && \
			ft_destroy_tool(&proc))
		return (0);
	printf("error\n");
	return (0);
}
