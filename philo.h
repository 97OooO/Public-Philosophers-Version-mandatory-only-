/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osslakri <osslakri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:30:48 by osslakri          #+#    #+#             */
/*   Updated: 2024/12/03 00:16:03 by osslakri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>

struct	s_data;

typedef struct s_philosopher
{
	int					id;
	int					meal_nbr;
	int					left_fork_id;
	int					right_fork_id;
	long long			t_last_meal;
	pthread_t			thread_id;
	struct s_data		*data;
}						t_philosopher;

typedef struct s_data
{
	int					philo_nbr;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_meals;
	long long			first_timestamp;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		forks[200];
	pthread_mutex_t		write_access;
	t_philosopher		philosophers[200];
}						t_data;

int						init_data(t_data *data, char **argv);
int						fraught(char *av);
int						init_mutex(t_data *data);
int						init_philosophers(t_data *data);
int						check_ate(t_data *data, t_philosopher *p);

int						ft_atoi(const char *str);
void					ft_print(t_data *data, int id, const char *message);
long long				timestamp(void);
long long				time_diff(long long past, long long pres);
void					ft_usleep(long long time);

int						start_routine(t_data *data);
void					eating(t_philosopher *philo);
void					*routine(void *void_philosopher);
void					monitor(t_data *data, t_philosopher *p);
void					end_routine(t_data *data);

#endif