/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:58:56 by masase            #+#    #+#             */
/*   Updated: 2025/02/06 18:43:23 by maw              ###   ########.fr       */
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
	usleep(philo->time_to_sleep);
	return 1;
}

int eating(t_philo *philo)
{
	printf("philo %d is eating...\n", philo->id);
	philo->meals_done++;
	usleep(philo->time_to_eat);
	printf("philo %d a fini de manger\n", philo->id);
	return 1;
}

void    *routine_even(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while(philo->num_of_must_eat != philo->meals_done)
	{
		think(philo);
		pthread_mutex_lock(philo->left_fork_mutex);
		printf("philo %d took left fork...\n", philo->id);
		pthread_mutex_lock(philo->right_fork_mutex);
		printf("philo %d took right fork...\n", philo->id);
		eating(philo);
		pthread_mutex_unlock(philo->left_fork_mutex);
		printf("philo %d let left fork...\n", philo->id);
		pthread_mutex_unlock(philo->right_fork_mutex);
		printf("philo %d let right fork...\n", philo->id);
		sleeping(philo);
	}
	return (NULL);
}
void    *routine_odd(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while(philo->num_of_must_eat != philo->meals_done)
	{
		think(philo);
		pthread_mutex_lock(philo->right_fork_mutex);
		printf("philo %d took right fork...\n", philo->id);
		pthread_mutex_lock(philo->left_fork_mutex);
		printf("philo %d took left fork...\n", philo->id);
		eating(philo);
		pthread_mutex_unlock(philo->right_fork_mutex);
		printf("philo %d let right fork...\n", philo->id);
		pthread_mutex_unlock(philo->left_fork_mutex);
		printf("philo %d let left fork...\n", philo->id);
		sleeping(philo);
	}
	return (NULL);
}

int	trader(t_monitor *monitor)
{
	create_mutex(monitor);
	create_thread(monitor);
	thread_join(monitor);
	mutex_destroy(monitor);
	return (1);
}
