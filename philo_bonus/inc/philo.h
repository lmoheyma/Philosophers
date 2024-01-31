/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:31:12 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/12/23 00:27:09 by lmoheyma         ###   ########.fr       */
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
# include <semaphore.h>
# include <fcntl.h>

struct	s_philo;

typedef struct s_data
{
	long int		start;
	int				nb_philos;
	int				nb_forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	int				*pid;
	sem_t			**philos;
	sem_t			*mutex;
	sem_t			*mutex_p;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				flag;
	int				count_eat;
	long int		last_meal;
	sem_t			*mutex_eat;
	t_data			*data;
	int				nb_locked_forks;
}					t_philo;

int					init(t_data *data, int argc, char **argv);
int					create_philo(t_data *data, int i, int flag);
void				*routine(void *arg);
void				monitor(t_data *data);
int					create_thread_even(t_data *data);
int					create_thread_odd(t_data *data);
void				clear_mutex(t_data *data);
int					ft_atoi(const char *str);
void				print_action(t_philo *philos, char *str);
int					check_stop(t_philo *philos);
int					check_args(int argc, char **argv);

// Time functions
long long			get_cur_time(void);
void				ft_usleep(int ms);

#endif