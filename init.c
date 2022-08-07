/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 22:46:26 by amessah           #+#    #+#             */
/*   Updated: 2022/08/06 23:51:28 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_ph_data *philo_data)
{
	int	i;

	i = philo_data->nb_ph;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(philo_data->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(philo_data->msg), NULL))
		return (1);
	if (pthread_mutex_init(&(philo_data->meal), NULL))
		return (1);
	return (0);
}

int	init_philo_list(t_ph_data *philo_data)
{
	int	i;

	i = philo_data->nb_ph;
	while (--i >= 0)
	{
		philo_data->philo[i].ph_id = i;
		philo_data->philo[i].ph_ate = 0;
		philo_data->philo[i].left_fork = i;
		philo_data->philo[i].right_fork = (i + 1) % philo_data->nb_ph;
		philo_data->philo[i].last_ph_meal = 0;
		philo_data->philo[i].ph_done_eating = 0;
		philo_data->philo[i].ph_data = philo_data;
	}
	return (0);
}

int	intialise(t_ph_data *philo_data, char **argv)
{
	philo_data->nb_ph = ft_atoi(argv[1]);
	philo_data->t_to_die = ft_atoi(argv[2]);
	philo_data->t_to_eat = ft_atoi(argv[3]);
	philo_data->t_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		if (ft_atoi(argv[5]) < 1)
			return (1);
		else
			philo_data->nb_eat = ft_atoi(argv[5]);
	}
	else
		philo_data->nb_eat = -1;
	philo_data->all_ate = 0;
	philo_data->ph_died = 0;
	if (philo_data->nb_ph < 1 || philo_data->t_to_die < 0
		|| philo_data->t_to_eat < 0 || philo_data->t_to_sleep < 0)
		return (1);
	if (init_mutex(philo_data))
		return (1);
	init_philo_list(philo_data);
	return (0);
}
