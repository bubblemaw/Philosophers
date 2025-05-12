/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:58:56 by masase            #+#    #+#             */
/*   Updated: 2025/05/12 12:52:52 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	think(t_philo *philo)
{
	printf("%ld %d is thinking...\n",
		(get_time() - philo->monitor->simu_start), philo->id);
	philo->think_flag = 1;
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
	philo->think_flag = 0;
	return (1);
}

int	eating(t_philo *philo)
{
	size_t	start_time;
	size_t	current_time;

	printf("%ld %d is eating...\n",
		(get_time() - philo->monitor->simu_start), philo->id);
	philo->eating = 1;
	start_time = get_time();
	current_time = get_time();
	pthread_mutex_lock(philo->meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->meal);
	while (philo->time_to_eat >= current_time - start_time)
	{
		usleep(500);
		current_time = get_time();
		if (philo->monitor->dead == 1)
		{
			unlock_fork(philo);
			return (0);
		}
	}
	philo->eating = 0;
	philo->meals_done++;
	philo->think_flag = 0;
	unlock_fork(philo);
	return (1);
}

void    *routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->monitor->dead != 1)
	{
		think(philo);
		if (philo->id % 2 == 0)
			usleep(7000);
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

void    *routine_last(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->monitor->dead != 1)
	{
		think(philo);
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
			if (check_dead(&monitor->philo[i]) == 0)
				return (NULL);
			if (monitor->meals_counter_flag == 1
				&& meals_manager(monitor, &meals_done_flag, i) == 0)
			{
				monitor->dead = 1;
				return (NULL);
			}
			current_time = get_time();
			i++;
		}
	}
}

int meals_manager(t_monitor *monitor, int *meals_done_flag, int i)
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

int	simu_start(t_monitor *monitor)
{
	create_mutex(monitor);
	create_thread(monitor);
	thread_join(monitor);
	mutex_destroy(monitor);
	return (1);
}
