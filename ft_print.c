/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osslakri <osslakri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 23:37:00 by osslakri          #+#    #+#             */
/*   Updated: 2024/12/02 23:13:51 by osslakri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_data *data, int id, const char *message)
{
	pthread_mutex_lock(&(data->write_access));
	printf("%lli %d %s\n", timestamp() - \
	data->first_timestamp, id + 1, message);
	pthread_mutex_unlock(&(data->write_access));
}
