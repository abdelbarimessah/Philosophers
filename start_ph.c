/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_ph.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 23:41:45 by amessah           #+#    #+#             */
/*   Updated: 2022/08/07 01:37:16 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_eat(t_philo_list *philo)
{
	t_ph_data	*philo_data;

	philo_data = philo->ph_data;
	pthread_mutex_lock(&(philo_data->forks[philo->left_fork]));
	put_msg(philo_data, philo->ph_id, "has taken a fork");
	pthread_mutex_lock(&(philo_data->forks[philo->right_fork]));
	put_msg(philo_data, philo->ph_id, "has taken a fork");
	pthread_mutex_lock(&(philo_data->meal));
	put_msg(philo_data, philo->ph_id, "is eating");
	philo->last_ph_meal = get_time();
	pthread_mutex_unlock(&(philo_data->meal));
	t_to_sleep(philo_data->t_to_eat, philo_data);
	(philo->ph_ate)++;
	pthread_mutex_unlock(&(philo_data->forks[philo->left_fork]));
	pthread_mutex_unlock(&(philo_data->forks[philo->right_fork]));
}

void	*routine(void *void_philo)
{
	t_philo_list	*philo;
	t_ph_data		*philo_data;

	philo = (t_philo_list *)void_philo;
	philo_data = philo->ph_data;
	if (philo->ph_id % 2)
		usleep(1000);
	while (!(philo_data->ph_died) && !(philo->ph_done_eating))
	{
		start_eat(philo);
		if (philo_data->nb_eat != -1 && philo->ph_ate >= philo_data->nb_eat)
		{
			philo->ph_done_eating = 1;
			break ;
		}
		if (philo_data->all_ate)
			break ;
		put_msg(philo_data, philo->ph_id, "is sleeping");
		t_to_sleep(philo_data->t_to_sleep, philo_data);
		put_msg(philo_data, philo->ph_id, "is thinking");
		usleep(50);
	}
	return (NULL);
}

void	check_ph_death(t_ph_data *philo_data, t_philo_list *philo)
{
	int	i;
	int	cont;

	while (!(philo_data->all_ate))
	{
		i = -1;
		while (++i < philo_data->nb_ph && !(philo_data->ph_died))
		{
			if (time_dif(philo[i].last_ph_meal, get_time())
				>= philo_data->t_to_die && philo[i].ph_done_eating != 1)
			{
				put_msg(philo_data, i, "died");
				philo_data->ph_died = 1;
			}
		}
		if (philo_data->ph_died)
			break ;
		i = -1;
		cont = 0;
		while (++i < philo_data->nb_ph && (philo_data->nb_eat) != -1)
			if (philo[i].ph_ate >= philo_data->nb_eat)
				cont++;
		if (cont == philo_data->nb_ph)
			philo_data->all_ate = 1;
	}
}

void	destroy_ph(t_ph_data *philo_data)
{
	int	i;

	i = -1;
	while (++i < philo_data->nb_ph)
		pthread_mutex_destroy(&(philo_data->forks[i]));
	pthread_mutex_destroy(&(philo_data->msg));
	pthread_mutex_destroy(&(philo_data->meal));
}

int	start_ph(t_ph_data *philo_data)
{
	int				i;
	t_philo_list	*philo;

	i = 0;
	philo = philo_data->philo;
	philo_data->time_start = get_time();
	while (i < philo_data->nb_ph)
	{
		if (pthread_create(&(philo[i].philo), NULL, routine, &(philo[i])))
			return (1);
		philo[i].last_ph_meal = get_time();
		pthread_detach(philo[i].philo);
		i++;
	}
	check_ph_death(philo_data, philo_data->philo);
	destroy_ph(philo_data);
	return (0);
}
