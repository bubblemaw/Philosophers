/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:58:56 by masase            #+#    #+#             */
/*   Updated: 2025/04/25 16:59:00 by masase           ###   ########.fr       */
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
	size_t done_time;

	done_time = 0;
	printf("philo %d is sleeping...\n", philo->id);
	while (done_time != philo->time_to_sleep)
	{
		usleep(100);
		done_time += 100;
		if (philo->monitor->dead == 1)
		{
			printf("philo %d quit...:(\n", philo->id);
			return (0);
		}
	}
	return 1;
}

int eating(t_philo *philo)
{
	size_t done_time;

	done_time = 0;
	philo->last_meal = get_time();
	philo->meals_done++;
	printf("philo %d is eating...\n", philo->id);
	while (done_time != philo->time_to_eat)
	{
		usleep(100);
		done_time += 100;
		if (philo->monitor->dead == 1)
		{
			pthread_mutex_unlock(philo->left_fork_mutex);
			pthread_mutex_unlock(philo->right_fork_mutex);
			printf("philo %d quit...:(\n", philo->id);
			return (0);
		}

	}
	printf("philo %d a fini de manger\n", philo->id);
	return 1;
}

void    *routine_even(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while(philo->monitor->dead != 1)
	{
		if (get_time() - philo->last_meal >= philo->time_to_die)
		{
			philo->dead = 1;
			printf("le PHILO NUMERO:%d EST MORTTTTTTTTTT\n", philo->id);
			break ;
		}
		printf("le monitor dead dans le philo est egal a :%d\n", philo->monitor->dead);
		think(philo);
		pthread_mutex_lock(philo->left_fork_mutex);
		printf("philo %d took left fork...\n", philo->id);
		pthread_mutex_lock(philo->right_fork_mutex);
		printf("philo %d took right fork...\n", philo->id);
		if (eating(philo) == 0)
			return (NULL);
		pthread_mutex_unlock(philo->left_fork_mutex);
		printf("philo %d let left fork...\n", philo->id);
		pthread_mutex_unlock(philo->right_fork_mutex);
		printf("philo %d let right fork...\n", philo->id);
		if (sleeping(philo) == 0)
			return (NULL);
	}
	return (NULL);
}
void    *routine_odd(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while(philo->monitor->dead != 1)
	{
		if (get_time() - philo->last_meal >= philo->time_to_die)
		{
			philo->dead = 1;
			printf("le PHILO NUMERO:%d EST MORTTTTTTTTTT\n", philo->id);
			break ;
		}
		printf("le monitor dead dans le philo est egal a :%d\n", philo->monitor->dead);
		think(philo);
		pthread_mutex_lock(philo->right_fork_mutex);
		printf("philo %d took right fork...\n", philo->id);
		pthread_mutex_lock(philo->left_fork_mutex);
		printf("philo %d took left fork...\n", philo->id);
		if (eating(philo) == 0)
			return (NULL);
		pthread_mutex_unlock(philo->right_fork_mutex);
		printf("philo %d let right fork...\n", philo->id);
		pthread_mutex_unlock(philo->left_fork_mutex);
		printf("philo %d let left fork...\n", philo->id);
		if (sleeping(philo) == 0)
			return (NULL);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	int i;
	int	num_philo;
	t_monitor *monitor;

	monitor = (t_monitor *)arg;
	printf("on est dans monitor routine\n");
	i = 0;
	num_philo = monitor->philo_number;
	while (1)
	{
		i = 0;
		while (i < num_philo)
		{
			if (monitor->philo[i].dead == 1)
			{
				printf("il faut mettre le monitor a 1\n");
				monitor->dead = 1;
				return (NULL);
			}
		i++;
		}
	}
	
}

int	trader(t_monitor *monitor)
{
	create_mutex(monitor);
	printf("go creer thread\n");
	create_thread(monitor);
	printf("go jointhread\n");
	thread_join(monitor);
	mutex_destroy(monitor);
	return (1);
}
