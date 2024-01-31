/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:45:01 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/12/22 19:36:38 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	data->mutex = malloc(sizeof(pthread_mutex_t) * data->nb_forks);
	if (!data->mutex)
		return (1);
	i = -1;
	while (++i < data->nb_forks)
	{
		if (pthread_mutex_init(&data->mutex[i], NULL))
			return (1);
	}
	if (pthread_mutex_init(&data->mutex_p, NULL))
		return (1);
	if (pthread_mutex_init(&data->mutex_stop, NULL))
		return (1);
	return (0);
}

void	philo_param(t_data *data, t_philo *philos, int flag)
{
	philos->count_eat = 0;
	philos->last_meal = data->start;
	philos->flag = flag;
	philos->data = data;
}

int	create_philo(t_data *data, int i, int flag)
{
	pthread_t	thread;
	t_philo		*philos;

	philos = malloc(sizeof(t_philo));
	if (!philos)
		return (1);
	philos->id = i;
	philo_param(data, philos, flag);
	if (pthread_mutex_init(&philos->mutex_eat, NULL))
		return (1);
	pthread_create(&thread, NULL, &routine, philos);
	data->thread[i] = thread;
	data->philos[i] = philos;
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->nb_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->nb_forks = data->nb_philos;
	if (argc == 6)
		data->max_eat = ft_atoi(argv[5]);
	else
		data->max_eat = -1;
	if (data->nb_philos == -1 || data->time_to_die == -1 || data->time_to_eat
		== -1 || data->time_to_sleep == -1)
		return (1);
	data->thread = malloc(sizeof(pthread_t) * data->nb_philos);
	data->philos = malloc(sizeof(t_philo *) * data->nb_philos);
	if (!data->thread || !data->philos)
		return (1);
	data->stop = 0;
	return (0);
}

int	init(t_data *data, int argc, char **argv)
{
	if (init_data(data, argc, argv) == -1)
		return (1);
	if (init_mutex(data))
		return (1);
	data->start = get_cur_time();
	if (create_thread_even(data))
		return (1);
	if (create_thread_odd(data))
		return (1);
	monitor(data);
	clear_mutex(data);
	return (0);
}
