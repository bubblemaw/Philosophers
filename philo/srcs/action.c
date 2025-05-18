/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:10:50 by maw               #+#    #+#             */
/*   Updated: 2025/05/16 17:27:43 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	think(t_philo *philo)
{
	printf("%ld %d is thinking...\n",
		(get_time() - philo->monitor->simu_start), philo->id);
	return (1);
}

int	sleeping(t_philo *philo)
{
	size_t	start_time;
	size_t	current_time;

	printf("%ld %d is sleeping...\n",
		(get_time() - philo->monitor->simu_start), philo->id);
	start_time = get_time();
	current_time = get_time();
	while (philo->time_to_sleep >= current_time - start_time)
	{
		usleep(500);
		current_time = get_time();
		if (philo->monitor->dead == 1)
			return (0);
	}
	return (1);
}

int	eating(t_philo *philo)
{
	size_t	start_time;
	size_t	current_time;

	printf("%ld %d is eating...\n",
		(get_time() - philo->monitor->simu_start), philo->id);
	start_time = get_time();
	current_time = get_time();
	pthread_mutex_lock(philo->meal);
	philo->eating = 1;
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->meal);
	while (philo->time_to_eat >= current_time - start_time)
	{
		usleep(500);
		current_time = get_time();
		pthread_mutex_lock(&philo->monitor->dead_mutex);
		if (philo->monitor->dead == 1)
		{
			pthread_mutex_unlock(&philo->monitor->dead_mutex);
			unlock_fork(philo);
			return (0);
		}
		pthread_mutex_unlock(&philo->monitor->dead_mutex);
	}
	pthread_mutex_unlock(&philo->monitor->dead_mutex);
	pthread_mutex_lock(philo->meal);
	philo->eating = 0;
	philo->meals_done++;
	pthread_mutex_unlock(philo->meal);
	unlock_fork(philo);
	return (1);
}

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->meal);
	if (philo->eating == 0)
	{
		// pthread_mutex_lock(philo->meal);
		if (get_time() - philo->last_meal
			> philo->time_to_die
			&& philo->eating == 0)
		{
			philo->dead = 1;
			// pthread_mutex_lock(&philo->monitor->dead_mutex);
			philo->monitor->dead = 1;
			printf("on est dans le lock\n");
			// pthread_mutex_unlock(&philo->monitor->dead_mutex);
			if (philo->left_fork_mutex)
				pthread_mutex_unlock(philo->left_fork_mutex);
			if (philo->right_fork_mutex)
				pthread_mutex_unlock(philo->right_fork_mutex);
			return (0);
		}
		// pthread_mutex_unlock(philo->meal);
	}
	pthread_mutex_unlock(philo->meal);
	return (1);
}
