/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:31:12 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/12/27 16:00:09 by lmoheyma         ###   ########.fr       */
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

struct	s_philo;

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
	pthread_t		*thread;
	struct s_philo	**philos;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	mutex_p;
	pthread_mutex_t	mutex_stop;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				flag;
	int				count_eat;
	long int		last_meal;
	pthread_mutex_t	mutex_eat;
	t_data			*data;
}					t_philo;

// Init
int					init(t_data *data, int argc, char **argv);
int					create_philo(t_data *data, int i, int flag);

// Philosophers functions
void				*routine(void *arg);
void				monitor(t_data *data);

// Start thread
int					create_thread_even(t_data *data);
int					create_thread_odd(t_data *data);

// Print
void				print_action(t_philo *philos, char *str);

// End program & clear
void				clear_mutex(t_data *data);
int					check_stop(t_philo *philos);

// Time functions
int					check_args(int argc, char **argv);
long long			get_cur_time(void);
void				ft_usleep(int ms);
int					ft_atoi(const char *str);

#endif