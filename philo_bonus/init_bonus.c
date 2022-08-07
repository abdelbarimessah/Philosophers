/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 04:23:25 by amessah           #+#    #+#             */
/*   Updated: 2022/08/06 23:51:28 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_semaphore(t_ph_data *philo_data)
{
	sem_unlink("/forks");
	sem_unlink("/msg");
	sem_unlink("/meal");
	philo_data->forks = sem_open("/forks", O_CREAT, S_IRWXU,
			philo_data->nb_ph);
	philo_data->msg = sem_open("/message", O_CREAT, S_IRWXU, 1);
	philo_data->meal = sem_open("/meal", O_CREAT, S_IRWXU, 1);
	if (philo_data->forks <= 0 || philo_data->msg <= 0
		|| philo_data->meal <= 0)
		exit(1);
	return (0);
}

void	init_philo_list(t_ph_data *philo_data)
{
	int	i;

	i = philo_data->nb_ph;
	while (--i >= 0)
	{
		philo_data->philo[i].ph_id = i;
		philo_data->philo[i].ph_ate = 0;
		philo_data->philo[i].last_ph_meal = 0;
		philo_data->philo[i].ph_done_eating = 0;
		philo_data->philo[i].ph_data = philo_data;
	}
}

int	initialise(t_ph_data *philo_data, char **argv)
{
	philo_data->nb_ph = ft_atoi(argv[1]);
	philo_data->t_to_die = ft_atoi(argv[2]);
	philo_data->t_to_eat = ft_atoi(argv[3]);
	philo_data->t_to_sleep = ft_atoi(argv[4]);
	philo_data->ph_died = 0;
	if (argv[5])
	{
		philo_data->nb_eat = ft_atoi(argv[5]);
		if (philo_data->nb_eat < 1)
			return (1);
	}
	else
		philo_data->nb_eat = -1;
	if (philo_data->nb_ph < 1 || philo_data->t_to_die < 0
		|| philo_data->t_to_eat < 0 || philo_data->t_to_sleep < 0)
		return (1);
	if (init_semaphore(philo_data))
		return (1);
	init_philo_list(philo_data);
	return (0);
}
