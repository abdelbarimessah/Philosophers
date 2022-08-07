/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_outils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:02:19 by amessah           #+#    #+#             */
/*   Updated: 2022/08/06 23:51:28 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_msg(t_ph_data *philo_data, int id, char *str)
{
	pthread_mutex_lock(&(philo_data->msg));
	if (!(philo_data->ph_died))
	{
		printf("%lli ", get_time() - philo_data->time_start);
		printf("%d ", id + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(philo_data->msg));
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
