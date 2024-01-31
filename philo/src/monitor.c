/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 19:33:41 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/12/22 19:33:41 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_stop(t_philo *philos)
{
	int	res;

	pthread_mutex_lock(&(philos->data->mutex_stop));
	res = philos->data->stop;
	pthread_mutex_unlock(&(philos->data->mutex_stop));
	return (res);
}

int	is_all_eat(t_philo *philos, int all_eat)
{
	if (philos->data->max_eat != -1 && all_eat == 1)
	{
		pthread_mutex_lock(&philos->data->mutex_stop);
		philos->data->stop = 1;
		pthread_mutex_unlock(&philos->data->mutex_stop);
		return (1);
	}
	return (0);
}

int	is_dead(t_data *data, t_philo *philos)
{
	if ((get_cur_time() - philos->last_meal) > data->time_to_die)
	{
		pthread_mutex_unlock(&philos->mutex_eat);
		print_action(philos, "died");
		pthread_mutex_lock(&philos->data->mutex_stop);
		philos->data->stop = 1;
		pthread_mutex_unlock(&philos->data->mutex_stop);
		return (1);
	}
	return (0);
}

void	monitor(t_data *data)
{
	int		i;
	int		all_eat;
	t_philo	*philos;

	while (1)
	{
		i = -1;
		all_eat = 1;
		while (++i < data->nb_philos)
		{
			philos = data->philos[i];
			pthread_mutex_lock(&philos->mutex_eat);
			if (is_dead(data, philos))
				return ;
			if (philos->count_eat < data->max_eat)
				all_eat = 0;
			pthread_mutex_unlock(&philos->mutex_eat);
		}
		if (is_all_eat(philos, all_eat))
			return ;
		usleep(3000);
	}
}
