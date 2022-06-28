/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:16:06 by schoe             #+#    #+#             */
/*   Updated: 2022/06/26 14:54:10 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <semaphore.h>

typedef struct s_philo
{
	int		name;
	int		die;
	int		eat;
	int		sleep;
	ssize_t	make;
	ssize_t	end_eat;
	int		eat_count;
	int		max_count;
	sem_t	*fork;
	sem_t	*print;
}	t_philo;

typedef struct s_proc
{
	int		number;
	sem_t	*fork;
	sem_t	*print;
	pid_t	*pid;
	t_philo	*philo;
}	t_proc;

//utils
int		ft_atoi(const char *str);
void	ft_msleep(int m_sec);
ssize_t	ft_get_usec(void);
int		ft_isdigit(int c);
//philo_simul
void	ft_sleep_think(t_philo *philo);
void	ft_eat(t_philo *philo);
void	ft_philo_simul(void *input);
int		ft_simul_start(t_proc *proc);
//monitor
void	*ft_view_philo(void	*philo);
int		ft_hungry_check(t_philo *philo);
int		ft_max_count_check(t_philo *philo);
//main
int		ft_proc_init(t_proc *proc, char **av);
int		ft_make_philo(t_proc *proc, char **av, int ac);
int		ft_destroy_tool(t_proc *proc);
int		ft_digit_check(char **av);

#endif
