/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:39:00 by maw               #+#    #+#             */
/*   Updated: 2025/01/31 17:02:37 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int philo_init(t_monitor *monitor, char **tab)
{
	int	i;

	i = 0;
	while(i < ft_atoi(tab[1]))
	{
		monitor->philo[i].id = i + 1;
		monitor->philo[i].number_of_philo = ft_atoi(tab[1]);
		monitor->philo[i].time_to_die = ft_atoi(tab[2]);
		monitor->philo[i].time_to_eat = ft_atoi(tab[3]);
		monitor->philo[i].time_to_sleep = ft_atoi(tab[4]);
		monitor->philo[i].num_of_must_eat = ft_atoi(tab[5]);
		i++;
	}
	return (1);
}
int print_philo(t_monitor *monitor)
{
	int	i;

	i = 0;
	while(i < monitor->philo->number_of_philo)
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
	t_monitor monitor;

	monitor.philo = malloc(ft_atoi(argv[1]) * sizeof(t_philo));
	if (argc == 5 || argc == 6)
	{
		philo_init(&monitor, argv);
		trader(&monitor);
		print_philo(&monitor);
	}
	return (0);
}
