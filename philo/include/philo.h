/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:31:12 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/12/20 00:27:59 by lmoheyma         ###   ########.fr       */
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

struct s_philo;

typedef struct s_data
{
	long int		start;
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	int				nb_forks;
	int				stop;
	int				die;
	struct s_philo	*philos;
	pthread_t		monitor;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	mutex_p;
	pthread_mutex_t mutex_d;
	pthread_mutex_t mutex_stop;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				count_eat;
	long int		last_meal;
	pthread_t		thread_p;
	int				left_fork;
	int				right_fork;
	t_data			*data;
}					t_philo;

int					init(t_data *data, int argc, char **argv);

//Time functions
long long			get_cur_time(void);
void				ft_usleep(int ms);

#endif