/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_thread_mutex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:08:08 by masase            #+#    #+#             */
/*   Updated: 2025/05/12 19:51:29 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
	int	ret;

	i = 0;
	ret = 1;
	while (i <= monitor->philo->number_of_philo - 1)
	{
		if (monitor->philo[i].left_fork_mutex)
		{
			if (pthread_mutex_destroy(monitor->philo[i].left_fork_mutex) != 0)
				ret = 0;
			free (monitor->philo[i].left_fork_mutex);
		}
		if (monitor->philo[i].meal)
		{
			if (pthread_mutex_destroy(monitor->philo[i].meal) != 0)
				ret = 0;
			free (monitor->philo[i].meal);
		}
		i++;
	}
	return (ret);
}
