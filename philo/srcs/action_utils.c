/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:47:47 by masase            #+#    #+#             */
/*   Updated: 2025/05/19 12:36:44 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	unlock_fork(t_philo *philo)
{
	if (philo->left_fork_mutex)
		pthread_mutex_unlock(philo->left_fork_mutex);
	if (philo->right_fork_mutex)
		pthread_mutex_unlock(philo->right_fork_mutex);
	return (0);
}

int	taking_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork_mutex);
	pthread_mutex_lock(&philo->monitor->dead_mutex);
	if (philo->monitor->dead == 1)
	{
		pthread_mutex_unlock(philo->left_fork_mutex);
		pthread_mutex_unlock(&philo->monitor->dead_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->monitor->dead_mutex);
	pthread_mutex_lock(&philo->monitor->print_mutex);
	printf("%ld %d has taken a fork...\n",
		get_time() - philo->monitor->simu_start, philo->id);
	pthread_mutex_unlock(&philo->monitor->print_mutex);
	pthread_mutex_lock(philo->right_fork_mutex);
	pthread_mutex_lock(&philo->monitor->dead_mutex);
	if (philo->monitor->dead == 1)
	{
		unlock_fork(philo);
		pthread_mutex_unlock(&philo->monitor->dead_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->monitor->dead_mutex);
	pthread_mutex_lock(&philo->monitor->print_mutex);
	printf("%ld %d has taken a fork...\n",
		get_time() - philo->monitor->simu_start, philo->id);
	pthread_mutex_unlock(&philo->monitor->print_mutex);
	return (1);
}

int	taking_fork_last_philo(t_philo *philo)
{
	while (1)
	{
		if (check_death_philo(philo) == 0)
			break ;
		if (philo->right_fork_mutex)
		{
			if (right_fork(philo) == 0)
			{
				pthread_mutex_unlock(&philo->monitor->dead_mutex);
				return (0);
			}
		}
		else
			continue ;
		if (philo->left_fork_mutex)
		{
			pthread_mutex_lock(philo->left_fork_mutex);
			if (philo->monitor->dead == 1)
			{
				unlock_fork(philo);
				pthread_mutex_unlock(&philo->monitor->dead_mutex);
				return (0);
			}
			pthread_mutex_lock(&philo->monitor->print_mutex);
			printf("%ld %d has taken a fork...\n",
				get_time() - philo->monitor->simu_start, philo->id);
			pthread_mutex_unlock(&philo->monitor->print_mutex);
			pthread_mutex_unlock(&philo->monitor->dead_mutex);
			return (1);
		}
		else
			continue ;
	}
	return (0);
}

int	right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork_mutex);
	if (philo->monitor->dead == 1)
	{
		pthread_mutex_unlock(philo->right_fork_mutex);
		return (0);
	}
	pthread_mutex_lock(&philo->monitor->print_mutex);
	printf("%ld %d has taken a fork...\n",
		get_time() - philo->monitor->simu_start, philo->id);
	pthread_mutex_unlock(&philo->monitor->print_mutex);
	return (1);
}
