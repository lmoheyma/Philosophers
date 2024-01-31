/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:31:58 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/12/20 01:41:08 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_action(t_philo *philos, char *str, int flag)
{
	pthread_mutex_lock(&philos->data->mutex_p);
	//pthread_mutex_lock(&philos->data->mutex_stop);
	if (!philos->data->die && !philos->data->stop)
		printf("%lld %i %s\n", get_cur_time() - philos->data->start, philos->id,
			str);
	//pthread_mutex_unlock(&philos->data->mutex_stop);
	if (flag)
		pthread_mutex_unlock(&philos->data->mutex_p);
}

void	*routine(void *arg)
{
	t_philo		*philos;
	t_data		*data;

	philos = (t_philo *)arg;
	data = philos->data;
	while (!data->die && !data->stop)
	{
		print_action(philos, "is thinking", 1);
		//if (philos->id % 2 == 0)
			pthread_mutex_lock(&philos->data->mutex[philos->left_fork]);
		//else
		//	pthread_mutex_lock(&philos->data->mutex[philos->right_fork]);
		print_action(philos, "has taken a fork", 1);
		//if (philos->id % 2 == 0)
			pthread_mutex_lock(&philos->data->mutex[philos->right_fork]);
		//else
		//	pthread_mutex_lock(&philos->data->mutex[philos->left_fork]);
		print_action(philos, "has taken a fork", 1);
		pthread_mutex_lock(&philos->data->mutex_d);
		print_action(philos, "is eating", 1);
		philos->last_meal = get_cur_time();
		pthread_mutex_unlock(&philos->data->mutex_d);
		ft_usleep(philos->data->time_to_eat);
		philos->count_eat++;
		// if (philos->id % 2 == 0)
		// {
			pthread_mutex_unlock(&philos->data->mutex[philos->right_fork]);
			pthread_mutex_unlock(&philos->data->mutex[philos->left_fork]);
		// }
		// else
		// {
		// 	pthread_mutex_unlock(&philos->data->mutex[philos->left_fork]);
		// 	pthread_mutex_unlock(&philos->data->mutex[philos->right_fork]);
		// }
		print_action(philos, "is sleeping", 1);
		ft_usleep(philos->data->time_to_sleep);
		//pthread_mutex_lock(&data->mutex_stop);
		// if (data->die)
		// {
		// 	pthread_mutex_unlock(&data->mutex_stop);
		// 	break ;
		// }
		// pthread_mutex_unlock(&data->mutex_stop);
	}
	return (0);
}

void	monitor(t_data *data, t_philo *philos)
{
	int		i;

	while (1)
	{
		i = -1;
		while (++i < data->nb_philos)
		{
			pthread_mutex_lock(&data->mutex_d);
			if ((get_cur_time() - philos[i].last_meal) >= data->time_to_die)
			{
				print_action(&philos[i], "died", 1);
				//pthread_mutex_lock(&data->mutex_stop);
				data->die = 1;
				//pthread_mutex_unlock(&data->mutex_stop);
			}
			pthread_mutex_unlock(&data->mutex_d);
		}
		if (data->die)
			break ;
		i = 0;
		while (data->max_eat != -1 && i < data->nb_philos && philos[i].count_eat >= data->max_eat)
			i++;
		// if (i == data->nb_philos)
		// 	break ;
		data->stop = (i == data->nb_philos);
	}
}

void	clear_mutex(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&data->mutex_p);
	pthread_mutex_destroy(&data->mutex_d);
	pthread_mutex_destroy(&data->mutex_stop);
	while (++i < data->nb_forks)
		pthread_mutex_destroy(&data->mutex[i]);
	free(data->philos);
	free(data->mutex);
}

int create_thread(t_data *data)
{
	int		i;

	i = 0;
	data->start = get_cur_time();
	while (i < data->nb_philos)
	{
		data->philos[i].last_meal = get_cur_time();
		if (pthread_create(&data->philos[i].thread_p, NULL, routine, &(data->philos[i])))
			return (1);
		usleep(50);
		i++;
	}
	monitor(data, data->philos);
	//pthread_mutex_unlock(&data->mutex_p);
	i = 0;
	if (data->nb_philos == 1)
		pthread_detach(data->philos[i].thread_p);
	else
	{
		while (i < data->nb_philos)
		{
			pthread_join(data->philos[i].thread_p, NULL);
			i++;
		}
	}
	clear_mutex(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (init(&data, argc, argv))
		return (1);
	if (create_thread(&data))
		return (1);
	return (0);
}
