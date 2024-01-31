/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:39:39 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/12/21 02:42:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int not_digit(char c)
{
	return (c < '0' || c > '9');
}

int	ft_atoi(const char *str)
{
	int			i;
	long int	res;

	i = 0;
	res = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (not_digit(str[i]))
			return (-1);
		res = res * 10 + (str[i] - '0');
		if (res > 2147483647 || res < -2147483648)
			return (-1);
		i++;
	}
	return (res);
}

void	print_action(t_philo *philos, char *str)
{
	pthread_mutex_lock(&philos->data->mutex_p);
	printf("%lld %i %s\n", get_cur_time() - philos->data->start, philos->id + 1,
			str);
	pthread_mutex_unlock(&philos->data->mutex_p);
}

long long	get_cur_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(int ms)
{
	long int	time;

	time = get_cur_time();
	while ((get_cur_time() - time) < ms)
		usleep(ms / 10);
}

