/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osslakri <osslakri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:30:54 by osslakri          #+#    #+#             */
/*   Updated: 2024/12/03 00:00:21 by osslakri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_overflow(int sign)
{
	if (sign < 0)
		return (0);
	else
		return (-1);
}

int	ft_atoi(const char *str)
{
	int			i[2];
	long int	result;
	long int	temp;

	1 && (i[0] = 0, i[1] = 1, result = 0);
	while (str[i[0]] == 32 || (str[i[0]] >= 9 && str[i[0]] <= 13))
		i[0]++;
	if (str[i[0]] == '-' || str[i[0]] == '+')
	{
		if (str[i[0]] == '-')
			i[1] = -1;
		i[0]++;
	}
	while (str[i[0]] >= '0' && str[i[0]] <= '9')
	{
		temp = result * 10 + (str[i[0]] - '0');
		if (result > temp && i[1] == 1)
			return (check_overflow(i[1]));
		else if (result > temp && i[1] == -1)
			return (0);
		1 && (result = temp, i[0]++);
	}
	if (str[i[0]] != '\0')
		return (-1);
	return (result * i[1]);
}

long long	timestamp(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) != 0)
		return (-1);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long pas, long long pres)
{
	return (pres - pas);
}

void	ft_usleep(long long time)
{
	long long	i;

	i = timestamp();
	while (1)
	{
		if (time_diff(i, timestamp()) >= time)
			break ;
		usleep(50);
	}
}
