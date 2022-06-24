/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:16:06 by schoe             #+#    #+#             */
/*   Updated: 2022/06/24 17:36:17 by schoe            ###   ########.fr       */
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
typedef struct	s_philo
{
	int	name;
	int	die_check;
	int	eat;
	int	sleep;
	ssize_t make;
	ssize_t end_eat;
	int	eat_count;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	*print;
}	t_philo;

typedef struct s_proc
{
	int number;
	int	die;
	int	max_count;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*print;
	pthread_t	*tid;
	t_philo	*philo;
}	t_proc;

//utils
int		ft_atoi(const char *str);
void	ft_die_check(t_proc *proc);
void	ft_msleep(int m_sec);
ssize_t	ft_get_usec(void);
//philo_simul
int		ft_sleep_think(t_philo *philo);
int		ft_odd_eat(t_philo *philo);
int		ft_even_eat(t_philo *philo);
void	*ft_philo_simul(void *input);
//proc
int		ft_view_philo(t_proc *proc);
int		ft_proc_init(t_proc *proc, char **av, int ac);
int		ft_make_philo(t_proc *proc, char **av);
int		ft_hungry_check(int i, t_proc *proc);
int		ft_max_count_check(t_proc *proc);
#endif
