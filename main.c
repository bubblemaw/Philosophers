/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:39:00 by maw               #+#    #+#             */
/*   Updated: 2025/04/26 14:25:03 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		monitor->philo[i].last_meal = get_time();
		monitor->philo[i].monitor = monitor;
		monitor->dead = 0;
		i++;
	}
	return (1);
}

int	print_philo(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->philo->number_of_philo)
	{
		printf("%d\n", monitor->philo[i].id);
		printf("%d\n", monitor->philo[i].number_of_philo);
		printf("%ld\n", monitor->philo[i].time_to_die);
		printf("%ld\n", monitor->philo[i].time_to_eat);
		printf("%ld\n", monitor->philo[i].time_to_sleep);
		printf("%d\n", monitor->philo[i].num_of_must_eat);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_monitor	monitor;

	monitor.philo = malloc(ft_atoi(argv[1]) * sizeof(t_philo));
	if (argc == 5 || argc == 6)
	{
		// printf("let's init philo\n");
		philo_init(&monitor, argv, argc);
		// printf("let's go into trader\n");
		trader(&monitor);
		// print_philo(&monitor);
	}
	free(monitor.philo);
	return (0);
}
