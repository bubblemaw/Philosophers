/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:10:50 by maw               #+#    #+#             */
/*   Updated: 2025/05/19 14:36:32 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->monitor->print_mutex);
	printf("%ld %d is thinking...\n",
		(get_time() - philo->monitor->simu_start), philo->id);
	pthread_mutex_unlock(&philo->monitor->print_mutex);
	return (1);
}

int	sleeping(t_philo *philo)
{
	size_t	start_time;
	size_t	current_time;

	pthread_mutex_lock(&philo->monitor->print_mutex);
	printf("%ld %d is sleeping...\n",
		(get_time() - philo->monitor->simu_start), philo->id);
	pthread_mutex_unlock(&philo->monitor->print_mutex);
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

	pthread_mutex_lock(&philo->monitor->print_mutex);
	printf("%ld %d is eating...\n",
		(get_time() - philo->monitor->simu_start), philo->id);
	pthread_mutex_unlock(&philo->monitor->print_mutex);
	start_time = get_time();
	current_time = get_time();
	activate_eating(philo);
	while (philo->time_to_eat >= current_time - start_time)
	{
		usleep(500);
		current_time = get_time();
		if (check_death_philo_eating(philo) == 0)
			return (0);
	}
	desactivate_eating(philo);
	return (1);
}

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->meal);
	if (get_time() - philo->last_meal
		> philo->time_to_die
		&& philo->eating == 0)
	{
		pthread_mutex_unlock(philo->meal);
		pthread_mutex_lock(&philo->monitor->dead_mutex);
		philo->dead = 1;
		philo->monitor->dead = 1;
		pthread_mutex_unlock(&philo->monitor->dead_mutex);
		return (0);
	}
	else
		pthread_mutex_unlock(philo->meal);
	return (1);
}
