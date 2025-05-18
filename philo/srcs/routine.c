/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:58:56 by masase            #+#    #+#             */
/*   Updated: 2025/05/16 17:52:02 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// if (philo->id % 2 == 0)
	// 	usleep(3000);
	while (philo->monitor->dead != 1)
	{
		think(philo);
		usleep(2000);
		if (taking_fork(philo) == 0)
			break ;
		if (eating(philo) == 0)
			break ;
		if (sleeping(philo) == 0)
			break ;
	}
	if (philo->dead == 1)
	{
		printf("%ld %d died\n",
			(get_time() - philo->monitor->simu_start), philo->id);
	}
	return (NULL);
}

void	*routine_last(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(3000);
	//philo->monitor->dead != 1
	while (philo->monitor->dead != 1)
	{
		think(philo);
		usleep(2000);
		if (philo->id % 2 == 0)
			usleep(3000);
		if (taking_fork_last_philo(philo) == 0)
			break ;
		if (eating(philo) == 0)
			break ;
		if (sleeping(philo) == 0)
			break ;
	}
	if (philo->dead == 1)
	{
		printf("%ld %d died\n",
			(get_time() - philo->monitor->simu_start), philo->id);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	int			i;
	int			meals_done_flag;
	size_t		current_time;
	t_monitor	*monitor;

	monitor = (t_monitor *)arg;
	meals_done_flag = 0;
	current_time = get_time();
	while (1)
	{
		i = 0;
		while (i < monitor->philo_number)
		{
			pthread_mutex_lock(&monitor->dead_mutex);
			if (check_dead(&monitor->philo[i]) == 0)
			{
				pthread_mutex_unlock(&monitor->dead_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&monitor->dead_mutex);
			if (monitor->meals_counter_flag == 1
				&& meals_counter(monitor, &meals_done_flag, i) == 0)
			{
				monitor->dead = 1;
				return (NULL);
			}
			current_time = get_time();
			i++;
		}
	}
}

int	meals_counter(t_monitor *monitor, int *meals_done_flag, int i)
{
	int	num_philo;

	num_philo = monitor->philo_number;
	if (monitor->philo[i].meals_done
		== monitor->philo[i].num_of_must_eat)
		*meals_done_flag = 1;
	else if (monitor->philo[i].meals_done
		!= monitor->philo[i].num_of_must_eat)
		*meals_done_flag = 0;
	if (*meals_done_flag == 1 && i == num_philo - 1)
		return (0);
	return (1);
}
