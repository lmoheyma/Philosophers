/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:52:51 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/12/26 17:52:51 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	is_dead(t_philo *philos)
{
	if ((get_cur_time() - philos->last_meal) > philos->data->time_to_die)
	{
		sem_post(philos->sem_eat);
		print_action(philos, "died", 1);
		if (philos->nb_locked_forks == 1)
			sem_post(philos->data->sem_fork);
		else if (philos->nb_locked_forks == 2)
		{
			sem_post(philos->data->sem_fork);
			sem_post(philos->data->sem_fork);
		}
		free_and_destroy(philos);
		exit(1);
	}
}

void	*monitor(void *arg)
{
	t_philo *philos;

	philos = (t_philo *)arg;
	while (1)
	{
		sem_wait(philos->sem_eat);
		is_dead(philos);
		if (philos->data->max_eat != -1
			&& philos->count_eat >= philos->data->max_eat)
		{
			sem_post(philos->sem_eat);
			if (philos->nb_locked_forks == 1)
				sem_post(philos->data->sem_fork);
			else if (philos->nb_locked_forks == 2)
			{
				sem_post(philos->data->sem_fork);
				sem_post(philos->data->sem_fork);
			}
			free_and_destroy(philos);
			exit(0);
		}
		sem_post(philos->sem_eat);
		usleep(2000);
	}
}
