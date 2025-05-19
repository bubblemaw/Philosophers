/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:20:18 by maw               #+#    #+#             */
/*   Updated: 2025/05/19 14:23:44 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->monitor->print_mutex);
	printf("%ld %d died\n",
		(get_time() - philo->monitor->simu_start), philo->id);
	pthread_mutex_unlock(&philo->monitor->print_mutex);
}

void	print_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->monitor->print_mutex);
	printf("%ld %d has taken a fork...\n",
		get_time() - philo->monitor->simu_start, philo->id);
	pthread_mutex_unlock(&philo->monitor->print_mutex);
}
