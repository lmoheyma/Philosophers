/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:31:12 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/12/27 15:50:47 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

struct	s_philo;

typedef struct s_data
{
	long int	start;
	int			nb_philos;
	int			nb_forks;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			max_eat;
	int			*pid;
	sem_t		**philos;
	sem_t		*sem_fork;
	sem_t		*sem_print;
}				t_data;

typedef struct s_philo
{
	int			id;
	int			flag;
	int			count_eat;
	long int	last_meal;
	sem_t		*sem_eat;
	t_data		*data;
	int			nb_locked_forks;
}				t_philo;

// Init
int				init(t_data *data, int argc, char **argv);
int				create_philo(t_data *data, int i, int flag);

// Philosophers functions
void			routine(t_philo *philos);
void			*monitor(void *arg);

// Start thread
int				create_thread_even(t_data *data);
int				create_thread_odd(t_data *data);

// Print
void			print_action(t_philo *philos, char *str, int is_dead);

// End program & clear
void			free_and_close(t_philo *philos);
void			exit_philo(t_data *data);

// Utils
int				ft_atoi(const char *str);
long long		get_cur_time(void);
void			ft_usleep(int ms);
int				check_args(int argc, char **argv);
int				ft_strlen(char *str);
char			*sem_name(char *name, int nb);

#endif