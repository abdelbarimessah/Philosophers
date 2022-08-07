/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_ph_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 00:47:12 by amessah           #+#    #+#             */
/*   Updated: 2022/08/07 01:37:47 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	start_eat(t_philo_list *philo)
{
	t_ph_data	*philo_data;

	philo_data = philo->ph_data;
	sem_wait(philo_data->forks);
	put_msg(philo_data, philo->ph_id, "has taken a fork");
	sem_wait(philo_data->forks);
	put_msg(philo_data, philo->ph_id, "has taken a fork");
	sem_wait(philo_data->meal);
	put_msg(philo_data, philo->ph_id, "is eating");
	philo->last_ph_meal = get_time();
	sem_post(philo_data->meal);
	t_to_sleep(philo_data->t_to_eat, philo_data);
	(philo->ph_ate)++;
	sem_post(philo_data->forks);
	sem_post(philo_data->forks);
}

void	*pros_func(void *void_philo)
{
	t_philo_list	*philo;
	t_ph_data		*philo_data;

	philo = (t_philo_list *)void_philo;
	philo_data = philo->ph_data;
	while (1)
	{
		if (philo->ph_done_eating == 1)
			break ;
		if (time_dif(philo->last_ph_meal, get_time()) > philo_data->t_to_die)
		{
			sem_wait(philo_data->meal);
			put_msg(philo_data, philo->ph_id, "died");
			philo_data->ph_died = 1;
			sem_post(philo_data->meal);
			sem_wait(philo_data->msg);
			exit(1);
		}
		usleep(1000);
	}
	return (NULL);
}

void	start_pr(t_philo_list *philo)
{
	t_ph_data	*philo_data;

	philo_data = philo->ph_data;
	philo->last_ph_meal = get_time();
	pthread_create(&(philo->philo_thread), NULL, pros_func, philo);
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
		put_msg(philo_data, philo->ph_id, "is sleeping");
		t_to_sleep(philo_data->t_to_sleep, philo_data);
		put_msg(philo_data, philo->ph_id, "is thinking");
		usleep(50);
	}
	pthread_join(philo->philo_thread, NULL);
	pthread_detach(philo->philo_thread);
	if (philo_data->ph_died)
		exit(1);
	exit(0);
}

int	start_ph(t_ph_data *philo_data)
{
	int				i;
	t_philo_list	*philo;

	i = -1;
	philo = philo_data->philo;
	philo_data->time_start = get_time();
	while (++i < philo_data->nb_ph)
	{
		philo[i].prosess_id = fork();
		if (philo[i].prosess_id < 0)
			return (1);
		if (philo[i].prosess_id == 0)
			start_pr(&(philo[i]));
		usleep(50);
	}
	close_ph(philo_data);
	return (0);
}

void	close_ph(t_ph_data *philo_data)
{
	int	i;
	int	k;

	i = -1;
	while (++i < philo_data->nb_ph)
	{
		waitpid(-1, &k, 0);
		if (k != 0)
		{
			i = -1;
			while (++i < philo_data->nb_ph)
				kill(philo_data->philo[i].prosess_id, 15);
			break ;
		}
	}
	sem_close(philo_data->forks);
	sem_close(philo_data->msg);
	sem_close(philo_data->meal);
	sem_unlink("/forks");
	sem_unlink("/msg");
	sem_unlink("/meal");
}
