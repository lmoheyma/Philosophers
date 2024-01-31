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

int	philo_lock_fork(t_philo *philos, int left_fork, int right_fork)
{
	if (left_fork == right_fork)
	{
		print_action(philos, "has taken a fork");
		ft_usleep(philos->data->time_to_die);
		return (1);
	}
	pthread_mutex_lock(&philos->data->mutex[left_fork]);
	if (check_stop(philos))
	{
		pthread_mutex_unlock(&philos->data->mutex[left_fork]);
		return (1);
	}
	print_action(philos, "has taken a fork");
	pthread_mutex_lock(&philos->data->mutex[right_fork]);
	if (check_stop(philos))
	{
		pthread_mutex_unlock(&philos->data->mutex[right_fork]);
		pthread_mutex_unlock(&philos->data->mutex[left_fork]);
		return (1);
	}
	print_action(philos, "has taken a fork");
	print_action(philos, "is eating");
	return (0);
}

int	eating(t_philo *philos, int left_fork, int right_fork)
{
	ft_usleep(philos->data->time_to_eat);
	if (check_stop(philos))
	{
		pthread_mutex_unlock(&philos->data->mutex[right_fork]);
		pthread_mutex_unlock(&philos->data->mutex[left_fork]);
		return (1);
	}
	pthread_mutex_lock(&philos->mutex_eat);
	philos->last_meal = get_cur_time();
	philos->count_eat++;
	pthread_mutex_unlock(&philos->mutex_eat);
	pthread_mutex_unlock(&philos->data->mutex[left_fork]);
	pthread_mutex_unlock(&philos->data->mutex[right_fork]);
	if (check_stop(philos))
		return (1);
	return (0);
}

void	philos_fork(t_philo *philos, int *left_fork, int *right_fork)
{
	int	tmp;

	*left_fork = philos->id;
	*right_fork = philos->id - 1;
	if (*right_fork == -1)
		*right_fork = philos->data->nb_forks - 1;
	if (*left_fork < *right_fork)
	{
		tmp = *left_fork;
		*left_fork = *right_fork;
		*right_fork = tmp;
	}
}

void	*routine(void *arg)
{
	t_philo	*philos;
	int		left_fork;
	int		right_fork;

	philos = (t_philo *)arg;
	philos_fork(philos, &left_fork, &right_fork);
	print_action(philos, "is thinking");
	if (philos->flag)
		ft_usleep(philos->data->time_to_eat);
	while (1)
	{
		if (philo_lock_fork(philos, left_fork, right_fork))
			return (0);
		if (eating(philos, left_fork, right_fork))
			return (0);
		print_action(philos, "is sleeping");
		ft_usleep(philos->data->time_to_sleep);
		if (check_stop(philos))
			return (0);
		print_action(philos, "is thinking");
	}
	return (0);
}
