/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osslakri <osslakri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:30:51 by osslakri          #+#    #+#             */
/*   Updated: 2024/12/03 13:04:11 by osslakri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philosopher *philo)
{
	t_data	*data;

	data = NULL;
	data = philo->data;
	pthread_mutex_lock(&(data->forks[philo->left_fork_id]));
	ft_print(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&(data->forks[philo->right_fork_id]));
	ft_print(data, philo->id, "has taken a fork");
	ft_print(data, philo->id, "is eating");
	pthread_mutex_lock(&(data->meal_check));
	philo->t_last_meal = timestamp();
	pthread_mutex_unlock(&(data->meal_check));
	ft_usleep(data->time_to_eat);
	(philo->meal_nbr)++;
	pthread_mutex_unlock(&(data->forks[philo->right_fork_id]));
	pthread_mutex_unlock(&(data->forks[philo->left_fork_id]));
}

void	*routine(void *void_philosopher)
{
	int				i;
	t_philosopher	*philo;
	t_data			*data;

	i = 0;
	philo = (t_philosopher *)void_philosopher;
	data = philo->data;
	if (philo->id % 2)
		usleep(data->time_to_eat);
	while (1)
	{
		if (data->philo_nbr == 1)
		{
			pthread_mutex_lock(&(data->forks[philo->left_fork_id]));
			ft_print(data, philo->id, "has taken a fork");
			pthread_mutex_unlock(&(data->forks[philo->left_fork_id]));
			break ;
		}
		eating(philo);
		ft_print(data, philo->id, "is sleeping");
		ft_usleep(data->time_to_sleep);
		ft_print(data, philo->id, "is thinking");
	}
	return (NULL);
}

void	end_routine(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
		pthread_mutex_destroy(&(data->forks[i]));
	pthread_mutex_destroy(&(data->write_access));
	pthread_mutex_destroy(&(data->meal_check));
}

void	monitor(t_data *data, t_philosopher *phs)
{
	int	i;

	i = 0;
	while (!(data == NULL || phs == NULL) && 1)
	{
		while (i < data->philo_nbr)
		{
			pthread_mutex_lock(&(data->meal_check));
			if (time_diff(phs[i].t_last_meal, timestamp()) > data->time_to_die)
			{
				pthread_mutex_lock(&(data->write_access));
				printf("%lld %d died\n", timestamp() - \
				data->first_timestamp, ++i);
				pthread_mutex_unlock(&(data->meal_check));
				return ;
			}
			pthread_mutex_unlock(&(data->meal_check));
			(usleep(100), i++);
		}
		i = 0;
		if (data->max_meals && check_ate(data, phs))
			break ;
	}
}

int	start_routine(t_data *data)
{
	int				i;
	t_philosopher	*philo;

	if (data == NULL)
		return (1);
	i = 0;
	philo = data->philosophers;
	data->first_timestamp = timestamp();
	while (i < data->philo_nbr)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, routine, &(philo[i])))
			return (1);
		pthread_detach(philo[i].thread_id);
		pthread_mutex_lock(&(data->meal_check));
		philo[i].t_last_meal = timestamp();
		pthread_mutex_unlock(&(data->meal_check));
		i++;
	}
	monitor(data, data->philosophers);
	end_routine(data);
	return (0);
}
