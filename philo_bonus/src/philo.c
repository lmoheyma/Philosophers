/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:31:58 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/12/27 02:33:21 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void free_sem(t_data *data)
{
	free(data->pid);
	free(data->philos);
}

void	free_and_destroy(t_philo *philos)
{
	free_sem(philos->data);
	sem_close(philos->sem_eat);
	sem_close(philos->data->sem_print);
	sem_close(philos->data->sem_fork);
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
