/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 02:03:18 by amessah           #+#    #+#             */
/*   Updated: 2022/08/07 01:36:31 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

typedef struct philo
{
	int				ph_id;
	int				ph_ate;
	int				ph_done_eating;
	int				left_fork;
	int				right_fork;
	long long int	last_ph_meal;
	pthread_t		philo;
	struct s_data	*ph_data;
}	t_philo_list;

typedef struct s_data
{
	int				nb_ph;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				nb_eat;
	int				ph_died;
	int				all_ate;
	long long int	time_start;
	pthread_mutex_t	meal;
	pthread_mutex_t	msg;
	pthread_mutex_t	forks[200];
	t_philo_list	philo[200];
}t_ph_data;

int				ft_atoi(const char *str);
int				intialise(t_ph_data *philo_data, char **argv);
int				init_philo_list(t_ph_data *philo_data);
int				init_mutex(t_ph_data *philo_data);
long long int	get_time(void);
void			put_msg(t_ph_data *philo_data, int id, char *str);
void			t_to_sleep(long long int time, t_ph_data *philo_data);
long long int	time_dif(long long int old, long long int new);
void			destroy_ph(t_ph_data *philo_data);
void			check_ph_death(t_ph_data *philo_data, t_philo_list *philo);
int				start_ph(t_ph_data *philo_data);
long long int	time_dif(long long int old, long long int new);
void			*routine(void *void_philo);

#endif