/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:16:19 by maw               #+#    #+#             */
/*   Updated: 2025/05/19 14:34:16 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	activate_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->meal);
	philo->eating = 1;
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->meal);
}

void	desactivate_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->meal);
	philo->eating = 0;
	philo->meals_done++;
	pthread_mutex_unlock(philo->meal);
	unlock_fork(philo);
}

int	check_death_philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->monitor->dead_mutex);
	if (philo->monitor->dead == 1)
	{
		pthread_mutex_unlock(&philo->monitor->dead_mutex);
		unlock_fork(philo);
		return (0);
	}
	else
		pthread_mutex_unlock(&philo->monitor->dead_mutex);
	return (1);
}
