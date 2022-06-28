/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:12:52 by schoe             #+#    #+#             */
/*   Updated: 2022/06/26 14:51:20 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <sys/time.h>
#include <unistd.h>

int	ft_atoi(const char *str)
{
	int		minus;
	size_t	sum;

	minus = 1;
	sum = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			minus *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		sum = (sum * 10) + (*str - '0');
		str++;
	}
	if (sum > 9223372036854775807 && minus == -1)
		return (0);
	else if (sum > 9223372036854775807)
		return (-1);
	return (minus * (int)sum);
}

void	ft_msleep(int m_sec)
{
	struct timeval	st;
	struct timeval	et;

	gettimeofday(&st, NULL);
	while (1)
	{
		gettimeofday(&et, NULL);
		if ((et.tv_sec - st.tv_sec) * 1000000 + \
				(et.tv_usec - st.tv_usec) >= m_sec * 1000)
			break ;
		usleep(100);
	}
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

ssize_t	ft_get_usec(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}
