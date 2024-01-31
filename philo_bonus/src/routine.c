/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 19:33:33 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/12/22 19:33:33 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_lock_fork(t_philo *philos)
{
	if (philos->data->nb_philos == 1)
	{
		print_action(philos, "has taken a fork", 0);
		ft_usleep(philos->data->time_to_die + 10);
	}
	sem_wait(philos->data->sem_fork);
	sem_wait(philos->sem_eat);
	philos->nb_locked_forks++;
	sem_post(philos->sem_eat);
	print_action(philos, "has taken a fork", 0);
	sem_wait(philos->data->sem_fork);
	sem_wait(philos->sem_eat);
	philos->nb_locked_forks++;
	sem_post(philos->sem_eat);
	print_action(philos, "has taken a fork", 0);
	print_action(philos, "is eating", 0);
}

void	eating(t_philo *philos)
{
	ft_usleep(philos->data->time_to_eat);
	sem_wait(philos->sem_eat);
	philos->last_meal = get_cur_time();
	philos->count_eat++;
	philos->nb_locked_forks -= 2;
	sem_post(philos->sem_eat);
	sem_post(philos->data->sem_fork);
	sem_post(philos->data->sem_fork);
}

void	routine(t_philo *philos)
{
	pthread_t	thread;

	if (philos->flag)
		ft_usleep(philos->data->time_to_eat);
	pthread_create(&thread, NULL, &monitor, philos);
	pthread_detach(thread);
	while (1)
	{
		philo_lock_fork(philos);
		eating(philos);
		print_action(philos, "is sleeping", 0);
		ft_usleep(philos->data->time_to_sleep);
		print_action(philos, "is thinking", 0);
	}
	exit(1);
}
