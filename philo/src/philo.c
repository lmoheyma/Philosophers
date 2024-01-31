/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:31:58 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/12/18 21:13:23 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_action(t_philo *philos, char *str)
{
	pthread_mutex_lock(&philos->data->mutex_p);
	pthread_mutex_lock(&philos->data->mutex_d);
	if (!philos->data->die)
		printf("%lld %i %s\n", get_cur_time() - philos->data->start, philos->id,
			str);
	pthread_mutex_unlock(&philos->data->mutex_p);
	pthread_mutex_unlock(&philos->data->mutex_d);
}

void	*routine(void *arg)
{
	t_philo		*philos;

	philos = arg;
	while (1)
	{
		print_action(philos, "is thinking");
		if (philos->id % 2 == 0)
			pthread_mutex_lock(philos->left_fork);
		else
			pthread_mutex_lock(philos->right_fork);
		print_action(philos, "has taken a fork");
		if (philos->id % 2 == 0)
			pthread_mutex_lock(philos->right_fork);
		else
			pthread_mutex_lock(philos->left_fork);
		print_action(philos, "has taken a fork");
		print_action(philos, "is eating");
		ft_usleep(philos->data->time_to_eat, philos);
		philos->last_meal = get_cur_time();
		if (philos->id % 2 == 0)
		{
			pthread_mutex_unlock(philos->left_fork);
			pthread_mutex_unlock(philos->right_fork);
		}
		else
		{
			pthread_mutex_unlock(philos->right_fork);
			pthread_mutex_unlock(philos->left_fork);
		}
		philos->count_eat++;
		print_action(philos, "is sleeping");
		ft_usleep(philos->data->time_to_sleep, philos);
	}
	return (0);
}

void	*monitor(void *arg)
{
	int		i;
	t_philo	*philos;

	philos = arg;
	while (1)
	{
		i = -1;
		while (++i < philos->data->nb_philos)
		{
			if (get_cur_time() - (philos
					+ i)->last_meal > philos->data->time_to_die)
			{
				print_action(philos + i, "died");
				pthread_mutex_lock(&philos->data->mutex_d);
				philos->data->die = 1;
				pthread_mutex_unlock(&philos->data->mutex_d);
				break ;
			}
			if (philos->data->max_eat != -1 && (philos
					+ i)->count_eat >= philos->data->max_eat)
			{
				pthread_mutex_lock(&philos->data->mutex_d);
				philos->data->die = 1;
				pthread_mutex_unlock(&philos->data->mutex_d);
			}
		}
		pthread_mutex_lock(&philos->data->mutex_d);
		if (philos->data->die == 1)
		{
			pthread_mutex_unlock(&philos->data->mutex_d);
			i = -2;
			break ;
		}
		if (i != -2)
			pthread_mutex_unlock(&philos->data->mutex_d);
	}
	return (0);
}

void	clear_mutex(t_philo *philos)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&philos->data->mutex_p);
	pthread_mutex_destroy(&philos->data->mutex_d);
	while (++i < philos->data->nb_forks)
		pthread_mutex_destroy(&philos->data->mutex[i]);
}

int	main(int argc, char **argv)
{
	t_philo	*philos;
	int		i;

	i = 0;
	if (init(&philos, argc, argv))
		return (1);
	philos->data->start = get_cur_time();
	while (i < philos->data->nb_philos)
	{
		if (philos->id % 2 == 0)
		{
			(philos + i)->last_meal = get_cur_time();
			if (pthread_create(&(philos + i)->thread_p, NULL, &routine, philos + i))
				return (1);
			usleep(50);
			//pthread_detach((philos + i)->thread_p);
		}
		i++;
	}
	i = 0;
	while (i < philos->data->nb_philos)
	{
		if (philos->id % 2 == 1)
		{
			(philos + i)->last_meal = get_cur_time();
			if (pthread_create(&(philos + i)->thread_p, NULL, &routine, philos + i))
				return (1);
			usleep(50);
			//pthread_detach((philos + i)->thread_p);
		}
		i++;
	}
	if (pthread_create(&philos->data->monitor, NULL, &monitor, philos))
		return (1);
	if (pthread_join(philos->data->monitor, NULL))
		return (1);
	i = 0;
	while (i < philos->data->nb_philos)
	{
		pthread_join((philos + i)->thread_p, NULL);
		i++;
	}
	usleep(50);
	clear_mutex(philos);
	return (0);
}
