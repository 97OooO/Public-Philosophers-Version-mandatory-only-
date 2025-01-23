/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osslakri <osslakri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:30:43 by osslakri          #+#    #+#             */
/*   Updated: 2024/12/03 12:55:36 by osslakri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		init_result;

	if (argc < 5 || argc > 6)
		return (write(2, "Number of arguments isn't valide!\n", 35), 1);
	init_result = init_data(&data, argv);
	if (init_result == -3)
		return (1);
	if (init_result == -1)
		return (write(2, "Something Wrong on your arguments!\n", 36), 1);
	else if (init_result == -2)
		return (write(2, "Error: Initializing Mutex!\n", 28), 1);
	if (start_routine(&data))
		return (write(2, "Error: Creating Threads!\n", 26), 1);
	return (0);
}
