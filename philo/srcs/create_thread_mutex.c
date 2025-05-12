/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread_mutex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:17:42 by maw               #+#    #+#             */
/*   Updated: 2025/05/12 19:51:38 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	create_mutex(t_monitor *monitor)
{
	int	i;
	int	num_philo;

	i = 0;
	num_philo = monitor->philo->number_of_philo;
	while (1)
	{
		monitor->philo[i].left_fork_mutex = malloc(sizeof(pthread_mutex_t));
		if (monitor->philo[i].left_fork_mutex == NULL)
			return (0);
		monitor->philo[i].meal = malloc(sizeof(pthread_mutex_t));
		if (monitor->philo[i].meal == NULL)
			return (0);
		if (num_philo == 1)
			break ;
		if (mutex_assignation(monitor, num_philo, i) == 0)
			return (0);
		if (i == num_philo - 1)
			break ;
		i++;
	}
	return (1);
}

int	mutex_assignation(t_monitor *monitor, int num_philo, int i)
{
	if (i == 0)
		monitor->philo[num_philo - 1].right_fork_mutex
			= monitor->philo[i].left_fork_mutex;
	else
		monitor->philo[i - 1].right_fork_mutex
			= monitor->philo[i].left_fork_mutex;
	if (pthread_mutex_init(monitor->philo[i].left_fork_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(monitor->philo[i].meal, NULL) != 0)
		return (0);
	return (1);
}

int	create_thread(t_monitor *monitor)
{
	int	i;

	i = 0;
	monitor->simu_start = get_time();
	while (1)
	{
		if (i != monitor->philo->number_of_philo - 1)
		{
			if (pthread_create(&monitor->philo[i].thread, NULL, routine,
					(void *)&monitor->philo[i]) != 0)
				return (0);
		}
		else if (i == monitor->philo->number_of_philo - 1)
		{
			if (pthread_create(&monitor->philo[i].thread, NULL, routine_last,
					(void *)&monitor->philo[i]) != 0)
				return (0);
		}
		if (create_monitor_thread(monitor, i) == 2)
			break ;
		i++;
	}
	return (1);
}

int	create_monitor_thread(t_monitor *monitor, int i)
{
	if (i == monitor->philo->number_of_philo - 1)
	{
		if (pthread_create(&monitor->thread, NULL, monitor_routine,
				(void *)monitor) != 0)
			return (0);
		return (2);
	}
	return (1);
}
