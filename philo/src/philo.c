/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:31:58 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/12/19 03:06:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_action(t_philo *philos, char *str, int flag)
{
	pthread_mutex_lock(&philos->data->mutex_p);
	if (!philos->data->die && !philos->data->stop)
		printf("%lld %i %s\n", get_cur_time() - philos->data->start, philos->id,
			str);
	if (flag)
		pthread_mutex_unlock(&philos->data->mutex_p);
}

void	*routine(void *arg)
{
	t_philo		*philos;

	philos = (t_philo *)arg;
	while (!philos->data->die && !philos->data->stop)
	{
		print_action(philos, "is thinking", 1);
		pthread_mutex_lock(&philos->data->mutex[philos->left_fork]);
		print_action(philos, "has taken a fork", 1);
		pthread_mutex_lock(&philos->data->mutex[philos->right_fork]);
		print_action(philos, "has taken a fork", 1);
		pthread_mutex_lock(&philos->data->mutex_d);
		print_action(philos, "is eating", 1);
		philos->last_meal = get_cur_time();
		pthread_mutex_unlock(&philos->data->mutex_d);
		ft_usleep(philos->data->time_to_eat, philos);
		philos->count_eat++;
		pthread_mutex_unlock(&philos->data->mutex[philos->right_fork]);
		pthread_mutex_unlock(&philos->data->mutex[philos->left_fork]);
		print_action(philos, "is sleeping", 1);
		ft_usleep(philos->data->time_to_sleep, philos);
	}
	return (0);
}

void	monitor(t_philo *philos)
{
	int		i;

	while (!philos->data->stop)
	{
		i = -1;
		while (++i < philos->data->nb_philos && !philos->data->die)
		{
			pthread_mutex_lock(&philos->data->mutex_d);
			if ((get_cur_time() - (philos
					+ i)->last_meal) >= philos->data->time_to_die)
			{
				print_action(philos + i, "died", 0);
				philos->data->die = 1;
			}
			pthread_mutex_unlock(&philos->data->mutex_d);
		}
		if (philos->data->die)
			break ;
		i = 0;
		while (philos->data->max_eat != -1 && i < philos->data->nb_philos && (philos + i)->count_eat >= philos->data->max_eat)
			i++;
		philos->data->stop = (i == philos->data->nb_philos);
	}
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
		(philos + i)->last_meal = get_cur_time();
		if (pthread_create(&(philos + i)->thread_p, NULL, &routine, philos + i))
			return (1);
		usleep(50);
		//pthread_detach((philos + i)->thread_p);
		i++;
	}
	// i = 0;
	// while (i < philos->data->nb_philos)
	// {
	// 	if (philos->id % 2 == 1)
	// 	{
	// 		(philos + i)->last_meal = get_cur_time();
	// 		if (pthread_create(&(philos + i)->thread_p, NULL, &routine, philos + i))
	// 			return (1);
	// 		usleep(50);
	// 		//pthread_detach((philos + i)->thread_p);
	// 	}
	// 	i++;
	// }
	monitor(philos);
	// if (pthread_create(&philos->data->monitor, NULL, &monitor, philos))
	// 	return (1);
	// if (pthread_join(philos->data->monitor, NULL))
	// 	return (1);
	pthread_mutex_unlock(&philos->data->mutex_p);
	i = 0;
	while (i < philos->data->nb_philos)
	{
		pthread_join((philos + i)->thread_p, NULL);
		i++;
	}
	//usleep(50);
	clear_mutex(philos);
	return (0);
}
