/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 04:16:23 by amessah           #+#    #+#             */
/*   Updated: 2022/08/07 01:37:31 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/time.h>
# include <signal.h>

typedef struct s_philo_list
{
	int				ph_id;
	int				ph_ate;
	int				ph_done_eating;
	int				left_fork;
	int				right_fork;
	long long int	last_ph_meal;
	pid_t			prosess_id;
	pthread_t		philo_thread;
	struct s_data	*ph_data;
}	t_philo_list;

typedef struct s_ph_data
{
	int				nb_ph;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				nb_eat;
	int				ph_died;
	int				all_ate;
	long long int	time_start;
	sem_t			*meal;
	sem_t			*msg;
	sem_t			*forks;
	t_philo_list	philo[200];
}t_ph_data;

long long int	get_time(void);
int				ft_atoi(const char *str);
void			put_msg(t_ph_data *philo_data, int id, char *str);
long long int	time_dif(long long int old, long long int new);
void			t_to_sleep(long long int time, t_ph_data *philo_data);
int				initialise(t_ph_data *philo_data, char **argv);
void			init_philo_list(t_ph_data *philo_data);
int				init_semaphore(t_ph_data *philo_data);
int				start_ph(t_ph_data *philo_data);
void			close_ph(t_ph_data *philo_data);

#endif