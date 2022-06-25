/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:16:06 by schoe             #+#    #+#             */
/*   Updated: 2022/06/25 14:37:11 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define L 0
# define R 1
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <signal.h>
typedef struct	s_philo
{
	int	name;
	int	die_check;
	int	die;
	int	eat;
	int	sleep;
	ssize_t make;
	ssize_t end_eat;
	int	eat_count;
	int	max_count;
	pid_t	pid;
	sem_t	*fork;
	sem_t	*print;
}	t_philo;

typedef struct s_proc
{
	int number;
	sem_t	*fork;
	sem_t	*print;
	pid_t	*pid;
	t_philo	*philo;
}	t_proc;

//utils
int		ft_atoi(const char *str);
void	ft_msleep(int m_sec);
ssize_t	ft_get_usec(void);
//philo_simul
int		ft_sleep_think(t_philo *philo);
int		ft_odd_eat(t_philo *philo);
int		ft_even_eat(t_philo *philo);
void	*ft_philo_simul(void *input);
//proc
void	*ft_view_philo(void	*philo);
int		ft_proc_init(t_proc *proc, char **av);
int		ft_make_philo(t_proc *proc, char **av, int ac);
int		ft_hungry_check(t_philo *philo);
int		ft_max_count_check(t_philo *philo);
#endif
