/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:44:53 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/12/22 19:37:50 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	not_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	overflow(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 10)
		return (1);
	return (0);
}

int	is_neg(char *str)
{
	if (ft_atoi(str) < 0)
		return (1);
	return (0);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (not_digit(argv[i]))
			return (1);
		if (overflow(argv[i]))
			return (1);
		if (is_neg(argv[i]))
			return (1);
		i++;
	}
	return (0);
}
