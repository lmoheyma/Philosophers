/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:31:58 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/12/16 20:19:32 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_cur_time(void)
{
	struct timeval time;

	if (gettimeofday(&time, NULL))
		return (-1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_action(t_philo *philos, char *str, int i)
{
	pthread_mutex_lock(&philos->data->mutex_p);
	printf("%ld %i %s", philos->data->start - get_cur_time(), i + 1, str);
	pthread_mutex_unlock(&philos->data->mutex_p);
}

void	*routine(void *arg)
{
	t_philo *philos;

	philos = arg;
	while (!philos->data->die)
	{
		pthread_mutex_lock(philos->left_fork);
		print_action(philos, "as taken a fork", philos->id);
		pthread_mutex_lock(philos->right_fork);
		print_action(philos, "as taken a fork", philos->id);
		print_action(philos, "is eating", philos->id);
		philos->data->last_meal = get_cur_time();
		philos->data->count_eat++;
		usleep(philos->data->time_to_eat);
		//sleep et augmenter le le cur time avec eat time
		pthread_mutex_unlock(philos->left_fork);
		pthread_mutex_unlock(philos->right_fork);
		print_action(philos, "is sleeping", philos->id);
		usleep(philos->data->time_to_sleep);
		//usleep, with sleep_time
		print_action(philos, "is thinking", philos->id);
		usleep(philos->data->time_to_sleep);
	}
}

int	monitor(void *arg)
{
	int	i;
	t_philo *philos;

	philos = arg;
	i = 0;
	while (!philos->data->die)
	{
		while (i < philos->data->nb_philos)
		{
			if (get_cur_time() - philos->data->last_meal > philos->data->time_to_die)
			{
				print_action(philos, "died", i);
				philos->data->die = 1;
				break ;
			}
		}
		if (philos->data->max_eat != -1 && philos->data->count_eat > philos->data->max_eat)
			philos->data->die = 1;
	}
	return (0);
}

int	thread_crea_and_destroy(int i)
{

}

int main(int argc, char *argv)
{
	t_data *data;
	t_philo *philos;
	int	i;
	
	i = 0;
	data->start = get_cur_time();
	if (init(data, philos, argc, argv))
		return (1);
	while (i < data->nb_philos)
	{
		if (pthread_create(&(philos[i]).thread_p, NULL, &routine, philos->thread_p))
			return (1);
		if (pthread_detach(&(philos[i]).thread_p))
			return (1);
		i++;
	}
	if (pthread_create(philos->data->monitor, NULL, &monitor, philos))
		return (1);
	if (pthread_join(philos->data->monitor, NULL))
		return (1);
	i = 0;
	while (i < data->nb_forks)
	{
		if (pthread_mutex_destroy(data->mutex + i))
			return (1);
		i++;
	}
	if (pthread_mutex_destroy(&data->mutex_p))
		return (1);
	return (0);
}
