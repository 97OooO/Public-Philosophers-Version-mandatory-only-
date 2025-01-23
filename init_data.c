/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osslakri <osslakri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:30:40 by osslakri          #+#    #+#             */
/*   Updated: 2024/12/03 12:53:22 by osslakri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fraught(char *av)
{
	int	i;

	i = -1;
	if (av[i] == '\0')
		return (1);
	while (av[++i])
		if (av[i] != ' ' && av[i] != '\t')
			return (1);
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = data->philo_nbr - 1;
	while (i >= 0)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL) != 0)
			return (1);
		i--;
	}
	if (pthread_mutex_init(&(data->write_access), NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(data->meal_check), NULL) != 0)
		return (1);
	return (0);
}

int	init_philosophers(t_data *data)
{
	int	i;

	i = data->philo_nbr - 1;
	while (i >= 0)
	{
		data->philosophers[i].id = i;
		data->philosophers[i].meal_nbr = 0;
		data->philosophers[i].left_fork_id = i;
		data->philosophers[i].right_fork_id = (i + 1) % data->philo_nbr;
		data->philosophers[i].t_last_meal = 0;
		data->philosophers[i].data = data;
		i--;
	}
	return (0);
}

int	init_data(t_data *data, char **argv)
{
	long long	a;

	data->philo_nbr = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->philo_nbr <= 0 || data->time_to_die < 0 || \
		data->time_to_eat < 0 || data->time_to_sleep < 0 || \
		data->philo_nbr > 200 || data->time_to_die < 60 || \
		data->time_to_sleep < 60 || data->time_to_eat < 60)
		return (-1);
	if (argv[5] && fraught(argv[5]))
	{
		data->max_meals = ft_atoi(argv[5]);
		if (data->max_meals <= 0)
			return (-1);
	}
	else
		data->max_meals = -1;
	a = timestamp();
	if (a == -1)
		return (write(2, "Error: gettimeofday failed\n", 28), -3);
	if (init_mutex(data))
		return (-2);
	return (init_philosophers(data), 0);
}

int	check_ate(t_data *data, t_philosopher *p)
{
	int	i;
	int	count;

	1 && (i = 0, count = 0);
	while (data->max_meals != -1 && i < data->philo_nbr)
	{
		pthread_mutex_lock(&(data->meal_check));
		if (p[i].meal_nbr >= data->max_meals)
			count++;
		pthread_mutex_unlock(&(data->meal_check));
		i++;
	}
	if (count == data->philo_nbr)
		return (1);
	return (0);
}
