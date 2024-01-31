/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:31:58 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/12/17 06:00:56 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_cur_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(int ms)
{
	long int	time;
	
	time = get_cur_time();
	while ((get_cur_time() - time) < ms)
		usleep(ms / 10);
}

void	print_action(t_philo *philos, char *str)
{
	pthread_mutex_lock(&philos->data->mutex_p);
	if (!philos->data->die)
		printf("%lld %i %s\n", get_cur_time() - philos->data->start, philos->id, str);
	pthread_mutex_unlock(&philos->data->mutex_p);
}

void	*routine(void *arg)
{
	t_philo *philos;
	
	philos = arg;
	while (!philos->data->die)
	{
		pthread_mutex_lock(philos->left_fork);
		print_action(philos, "has taken a fork");
		pthread_mutex_lock(philos->right_fork);
		print_action(philos, "has taken a fork");
		print_action(philos, "is eating");
		ft_usleep(philos->data->time_to_eat);
		philos->last_meal = get_cur_time();
		//printf("%lld\n", get_cur_time());
		//printf("%lld\n", get_cur_time());
		pthread_mutex_unlock(philos->left_fork);
		pthread_mutex_unlock(philos->right_fork);
		philos->count_eat++;
		print_action(philos, "is sleeping");
		ft_usleep(philos->data->time_to_sleep);
		print_action(philos, "is thinking");
	}
	return (0);
}

void	*monitor(void *arg)
{
	int	i;
	t_philo *philos;

	philos = arg;
	while (!philos->data->die)
	{
		i = -1;
		while (++i < philos->data->nb_philos)
		{
			if (get_cur_time() - (philos + i)->last_meal > philos->data->time_to_die)
			{
				print_action(philos + i, "died");
				philos->data->die = 1;
				break ;
			}
			if (philos->data->max_eat != -1 && (philos + i)->count_eat >= philos->data->max_eat)
				philos->data->die = 1;
		}
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_philo *philos;
	int	i;
	
	i = -1;
	if (init(&philos, argc, argv))
		return (1);
	philos->data->start = get_cur_time();
	while (++i < philos->data->nb_philos)
	{
		if (pthread_create(&(philos + i)->thread_p, NULL, &routine, philos + i))
			return (1);
		pthread_detach((philos + i)->thread_p);
		usleep(3000);
	}
	if (pthread_create(&philos->data->monitor, NULL, &monitor, philos))
		return (1);
	if (pthread_join(philos->data->monitor, NULL))
		return (1);
	i = 0;
	while (i < philos->data->nb_forks)
	{
		if (pthread_mutex_destroy(&philos->data->mutex[i]))
			return (1);
		i++;
	}
	if (pthread_mutex_destroy(&philos->data->mutex_p))
		return (1);
	return (0);
}
