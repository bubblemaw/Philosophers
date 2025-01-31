/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:58:56 by masase            #+#    #+#             */
/*   Updated: 2025/01/31 17:02:31 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int think(t_philo *philo)
{
	printf("philo %d is thinking...\n", philo->id);
	return (1);
}

int sleeping(t_philo *philo)
{
	printf("philo %d is sleeping...\n", philo->id);
	usleep(philo->time_to_sleep * MILLISECONDS);

	return 1;
}

int eating(t_philo *philo)
{
	printf("philo %d is eating...\n", philo->id);
	usleep(philo->time_to_eat * MILLISECONDS);
	return 1;
}

void    *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	think(philo);
	// pthread_mutex_lock(philo.fork_mutex);
	eating(philo);
	// pthread_mutex_unlock();
	sleeping(philo);
	return (NULL);
}
int	trader(t_monitor *monitor)
{
	int i;
	int j;

	i = 0;
	// pthread_mutex_init(philo)
	while (1)
	{
		pthread_create(&monitor->philo[i].thread, NULL, routine, (void *)&monitor->philo[i]);
		if (i == monitor->philo[i].number_of_philo - 1)
			break ; 
		i++;
	}
	i = 0;
	while (1)
	{
		pthread_join(monitor->philo[i].thread, NULL);
		if (i == monitor->philo[i].number_of_philo - 1)
			break ;
		i++;
	}
	return (1);
}