/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:58:20 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/12/16 18:26:08 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		res = res * 10 + (str[i] - '0');
		if (res * sign > 2147483647 || res * sign < -2147483648)
			return (-1);
		i++;
	}
	return (res * sign);
}

int	init_mutex(t_data *data)
{
	pthread_mutex_t	*mutex;
	int				i;

	i = 0;
	mutex = malloc(sizeof(pthread_mutex_t) * data->nb_forks);
	if (!mutex)
		return (1);
	while (i < data->nb_forks)
	{
		if (pthread_mutex_init(mutex + i, NULL))
			return (1);
		i++;
	}
	return (0);
}

void	init_philo(t_data *data, t_philo *philos, int i, pthread_mutex_t *fork)
{
	philos->id = i + 1;
	if (i == 1)
	{
		philos->left_fork = &fork[data->nb_forks];
		philos->right_fork = &fork[i];
	}
	else
	{
		philos->left_fork = &fork[i - 1];
		philos->right_fork = &fork[i];
	}
}

int	init_data(t_data *data, int argc, char **argv)
{
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->nb_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->nb_forks = ft_atoi(argv[1]);
	if (argc == 5)
		data->count_eat = ft_atoi(argv[5]);
	else
		data->count_eat = -1;
	if (data->nb_philos == -1 || data->time_to_die == -1 || data->time_to_eat ==
		-1 || data->time_to_sleep == -1)
		return (1);
	data->die = 0;
	return (0);
}

int init(t_data *data, t_philo *philos, int argc, char **argv)
{
	int	i;

	i = 1;
	data = init_data(data, argc, argv);
	if (data)
		return (1);
	if (pthread_init_t(philos->data->mutex_p, NULL))
		return (1);
	if (init_mutex(data))
		return (1);
	while (i <= data->nb_philos)
	{
		init_philo(data, philos, i, data->mutex);
		i++;
	}
	return (0);
}

