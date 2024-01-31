/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:31:12 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/12/17 05:54:08 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	long int		start;
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	int				nb_forks;
	int				die;
	pthread_t		monitor;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	mutex_p;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				count_eat;
	long int		last_meal;
	pthread_t		thread_p;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}					t_philo;

int					init(t_philo **philos, int argc, char **argv);

#endif