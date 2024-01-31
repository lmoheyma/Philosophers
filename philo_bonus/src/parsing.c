/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:45:01 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/12/26 21:02:54 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

char	*sem_name(char *name, int nb)
{	
	int	i;

	i = 5;
	name[0] = '/';
	name[1] = 's';
	name[2] = 'e';
	name[3] = 'm';
	name[4] = '_';
	while (nb > 0)
	{
		name[i++] = nb % 10 + '0';
		nb /= 10;
	}
	name[i] = '\0';
	return (name);
}

void	philo_param(t_data *data, t_philo *philos, int flag)
{
	philos->count_eat = 0;
	philos->last_meal = data->start;
	philos->flag = flag;
	philos->data = data;
	philos->nb_locked_forks = 0;
}

int	create_philo(t_data *data, int i, int flag)
{
	int			pid;
	char		name[251];
	t_philo		philos;

	philos.id = i;
	philo_param(data, &philos, flag);
	philos.sem_eat = sem_open(sem_name(name, i), O_CREAT, 0644, 1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		routine(&philos);
	else
	{
		data->pid[i] = pid;
		data->philos[i] = philos.sem_eat;
		return (0);
	}
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
	data->pid = malloc(sizeof(pthread_t) * data->nb_philos);
	data->philos = malloc(sizeof(t_philo *) * data->nb_philos);
	if (!data->pid || !data->philos)
		return (1);
	return (0);
}

void exit_philo(t_data *data)
{
	int status;
	int	i;
	char	name[251];

	i = -1;
	while (++i < data->nb_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < data->nb_philos)
				kill(data->pid[i], 15);
			break ;
		}
	}
	i = -1;
	while (++i < data->nb_philos)
	{
		sem_close(data->philos[i]);
		sem_unlink(sem_name(name, i));
	}
	sem_close(data->sem_fork);
	sem_close(data->sem_print);
	sem_unlink("/sem_print");
	sem_unlink("/sem_fork");
	free(data->pid);
	free(data->philos);
}

int	init(t_data *data, int argc, char **argv)
{
	if (init_data(data, argc, argv) == -1)
		return (1);
	data->sem_fork = sem_open("/sem_fork", O_CREAT, 0644, data->nb_forks);
	data->sem_print = sem_open("/sem_print", O_CREAT, 0644, 1);
	data->start = get_cur_time();
	if (create_thread_even(data))
		return (1);
	if (create_thread_odd(data))
		return (1);
	exit_philo(data);
	return (0);
}
