/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 00:06:39 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/12/27 15:53:02 by lmoheyma         ###   ########.fr       */
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

void	clear_sem(t_data *data)
{
	sem_close(data->sem_fork);
	sem_unlink("/sem_fork");
	sem_close(data->sem_print);
	sem_unlink("/sem_print");
	free(data->pid);
	free(data->philos);
}

void	exit_philo(t_data *data)
{
	int		status;
	int		i;
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
	clear_sem(data);
}
