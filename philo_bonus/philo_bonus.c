/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 04:16:13 by amessah           #+#    #+#             */
/*   Updated: 2022/08/07 01:06:59 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_ph_data	philo_data;

	if (argc != 5 && argc != 6)
	{
		write(2, "Wrong Amount Of Argument\n", 39);
		return (1);
	}
	if (initialise(&philo_data, argv))
	{
		write(1, "Error En Enitializing Data", 27);
		return (2);
	}
	if (start_ph(&philo_data))
	{
		write(1, "Error In Creating Threads", 26);
		return (3);
	}
	return (0);
}
