/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:39:00 by maw               #+#    #+#             */
/*   Updated: 2025/05/19 14:19:49 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	philo_init(t_monitor *monitor, char **tab, int argc)
{
	int	i;

	i = 0;
	monitor->philo_number = ft_atoi(tab[1]);
	while (i < ft_atoi(tab[1]))
	{
		monitor->philo[i].id = i + 1;
		monitor->philo[i].number_of_philo = ft_atoi(tab[1]);
		monitor->philo[i].time_to_die = ft_atoi(tab[2]);
		monitor->philo[i].time_to_eat = ft_atoi(tab[3]);
		monitor->philo[i].time_to_sleep = ft_atoi(tab[4]);
		if (argc == 6)
			monitor->philo[i].num_of_must_eat = ft_atoi(tab[5]);
		monitor->philo[i].dead = 0;
		monitor->philo[i].meals_done = 0;
		monitor->philo[i].eating = 0;
		monitor->philo[i].monitor = monitor;
		monitor->dead = 0;
		monitor->philo[i].last_meal = get_time();
		i++;
	}
	return (1);
}

int	check_numerical_args(char **tab)
{
	int	i;
	int	j;

	i = 1;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] >= '0' && tab[i][j] <= '9')
				j++;
			else
			{
				return (0);
			}
		}
		i++;
	}
	return (i);
}

int	simu_start(t_monitor *monitor)
{
	create_mutex(monitor);
	create_thread(monitor);
	thread_join(monitor);
	mutex_destroy(monitor);
	return (1);
}

int	main(int argc, char **argv)
{
	t_monitor	monitor;

	memset(&monitor, 0, sizeof(t_monitor));
	if (argc == 6)
		monitor.meals_counter_flag = 1;
	if (argc == 5 || argc == 6)
	{
		if (check_numerical_args(argv) == 0)
			return (0);
		monitor.philo = malloc(ft_atoi(argv[1]) * sizeof(t_philo));
		if (monitor.philo == NULL)
			return (0);
		philo_init(&monitor, argv, argc);
		simu_start(&monitor);
		free(monitor.philo);
	}
	return (0);
}
