/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:58:56 by masase            #+#    #+#             */
/*   Updated: 2025/05/19 14:35:29 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(3000);
	while (1)
	{
		if (check_death_philo(philo) == 0)
			break ;
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
		print_died(philo);
	return (NULL);
}

void	*routine_last(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(3000);
	while (1)
	{
		if (check_death_philo(philo) == 0)
			break ;
		think(philo);
		usleep(2000);
		if (taking_fork_last_philo(philo) == 0)
			break ;
		if (eating(philo) == 0)
			break ;
		if (sleeping(philo) == 0)
			break ;
	}
	if (philo->dead == 1)
		print_died(philo);
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

int	check_death_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->monitor->dead_mutex);
	if (philo->monitor->dead == 1)
	{
		pthread_mutex_unlock(&philo->monitor->dead_mutex);
		return (0);
	}
	else
		pthread_mutex_unlock(&philo->monitor->dead_mutex);
	return (1);
}
