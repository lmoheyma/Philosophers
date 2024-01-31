/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:31:58 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/12/22 19:33:22 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	clear_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
		pthread_join(data->thread[i], NULL);
	i = -1;
	pthread_mutex_destroy(&data->mutex_p);
	pthread_mutex_destroy(&data->mutex_stop);
	while (++i < data->nb_forks)
		pthread_mutex_destroy(&data->mutex[i]);
	i = -1;
	while (++i < data->nb_philos)
		free(data->philos[i]);
	free(data->mutex);
	free(data->thread);
	free(data->philos);
}

int	create_thread_even(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (create_philo(data, i, 0))
			return (1);
		i += 2;
	}
	return (0);
}

int	create_thread_odd(t_data *data)
{
	int	i;

	i = 1;
	while (i < data->nb_philos)
	{
		if (create_philo(data, i, 1))
			return (1);
		i += 2;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (1);
	if (check_args(argc, argv))
		return (1);
	if (init(&data, argc, argv))
		return (1);
	return (0);
}
