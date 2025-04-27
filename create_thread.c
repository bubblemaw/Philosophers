/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:17:42 by maw               #+#    #+#             */
/*   Updated: 2025/04/26 14:30:08 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		if (i == 0)
			monitor->philo[num_philo - 1].right_fork_mutex = monitor->philo[i].left_fork_mutex;
		else
			monitor->philo[i - 1].right_fork_mutex = monitor->philo[i].left_fork_mutex;
		if (pthread_mutex_init(monitor->philo[i].left_fork_mutex, NULL) != 0)
			return (0);
		if (i == num_philo - 1)
			break ;
		i++;
	}
	return (1);
}

int	create_thread(t_monitor *monitor)
{
	int	i;
	int	num_philo;

	i = 0;
	num_philo = monitor->philo->number_of_philo;
	i = 0;
	monitor->simu_start = get_time();
	while (1)
	{
		if (monitor->philo[i].id % 2 == 0)
		{
			if (pthread_create(&monitor->philo[i].thread, NULL, routine_even, (void *)&monitor->philo[i]) != 0)
			return (0);
		}
		else
		{
			if (pthread_create(&monitor->philo[i].thread, NULL, routine_odd, (void *)&monitor->philo[i]) != 0)
			return (0);
		}
		if (i == num_philo - 1)
		{
			// printf("on cree le monitor thread\n");
			pthread_create(&monitor->thread, NULL, monitor_routine, (void *)monitor);
			break ;
		}
		i++;
	}
	return (1);
}

int	thread_join(t_monitor *monitor)
{
	int	i;
	int	num_philo;

	num_philo = monitor->philo->number_of_philo;
	i = 0;
	while (1)
	{
		if (pthread_join(monitor->philo[i].thread, NULL) != 0)
			return (0);
		if (i == num_philo - 1)
		{
			// printf("on attend un thread\n");
			pthread_join(monitor->thread, NULL);
			break ;
		}
		i++;
	}
	return (1);
}

int	mutex_destroy(t_monitor *monitor)
{
	int	i;
	int	num_philo;

	num_philo = monitor->philo->number_of_philo;
	i = 0;
	while (1)
	{
		free (monitor->philo[i].left_fork_mutex);
		if (pthread_mutex_destroy(monitor->philo[i].left_fork_mutex) != 0)
			return (0);
		if (i == num_philo - 1)
			break ;
		i++;
	}
	return (1);
}
