/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:45:29 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/12/22 19:33:52 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
		res = res * 10 + (str[i] - '0');
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
