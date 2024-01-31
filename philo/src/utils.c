/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:39:39 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/12/21 02:14:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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

