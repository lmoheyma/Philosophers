/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:58:20 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/12/19 02:54:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
	int	i;

	i = -1;
	data->mutex = malloc(sizeof(pthread_mutex_t) * data->nb_forks);
	if (!data->mutex)
		return (1);
	while (++i < data->nb_forks)
	{
		if (pthread_mutex_init(data->mutex + i, NULL))
			return (1);
	}
	if (pthread_mutex_init(&data->mutex_d, NULL))
		return (1);
	if (pthread_mutex_init(&data->mutex_p, NULL))
		return (1);
	return (0);
}

void	init_philo(t_data *data, t_philo *philos, int i, pthread_mutex_t *fork)
{
	philos->id = i + 1;
	philos->count_eat = 0;
	philos->last_meal = 0;
	philos->data = data;
	philos->left_fork = i;
	philos->right_fork = (i + 1) % data->nb_philos;
}

int	init_data(t_data **data, int argc, char **argv)
{
	t_data	*data_tmp;

	data_tmp = malloc(sizeof(t_data));
	if (!data_tmp)
		return (1);
	data_tmp->nb_philos = ft_atoi(argv[1]);
	data_tmp->time_to_die = ft_atoi(argv[2]);
	data_tmp->time_to_eat = ft_atoi(argv[3]);
	data_tmp->time_to_sleep = ft_atoi(argv[4]);
	data_tmp->nb_forks = data_tmp->nb_philos;
	if (argc == 6)
		data_tmp->max_eat = ft_atoi(argv[5]);
	else
		data_tmp->max_eat = -1;
	if (data_tmp->nb_philos == -1 || data_tmp->time_to_die == -1
		|| data_tmp->time_to_eat == -1 || data_tmp->time_to_sleep == -1)
		return (1);
	data_tmp->die = 0;
	data_tmp->stop = 0;
	*data = data_tmp;
	return (0);
}

int	init(t_philo **philos, int argc, char **argv)
{
	int		i;
	t_data	*data;
	t_philo	*tmp_philos;

	if (argc < 5)
		return (1);
	i = -1;
	if (init_data(&data, argc, argv) == -1)
		return (1);
	if (init_mutex(data))
		return (1);
	tmp_philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!tmp_philos)
		return (1);
	while (++i < data->nb_philos)
	{
		init_philo(data, tmp_philos + i, i, data->mutex);
	}
	*philos = tmp_philos;
	return (0);
}
