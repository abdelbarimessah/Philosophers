/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_outils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 04:16:01 by amessah           #+#    #+#             */
/*   Updated: 2022/08/06 23:51:28 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long int	get_time(void)
{
	struct timeval	current;
	long long int	res;

	gettimeofday(&current, NULL);
	res = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (res);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\n')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result * sign);
}

void	put_msg(t_ph_data *philo_data, int id, char *str)
{
	sem_wait(philo_data->msg);
	if (!(philo_data->ph_died))
	{
		printf("%lli ", get_time() - philo_data->time_start);
		printf("%d ", id + 1);
		printf("%s\n", str);
	}
	sem_post(philo_data->msg);
}

long long int	time_dif(long long int old, long long int new)
{
	long long int	res;

	res = new - old;
	return (res);
}

void	t_to_sleep(long long int time, t_ph_data *philo_data)
{
	long long	i;

	i = get_time();
	while (!(philo_data->ph_died))
	{
		if (time_dif(i, get_time()) >= time)
			break ;
		usleep(50);
	}
}
