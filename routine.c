/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:58:56 by masase            #+#    #+#             */
/*   Updated: 2025/04/26 14:32:44 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	think(t_philo *philo)
{
	printf("%ld philo %d is thinking...\n",
		(get_time() - philo->monitor->simu_start), philo->id);
	return (1);
}

int	sleeping(t_philo *philo)
{
	size_t	done_time;

	done_time = 0;
	printf("%ld philo %d is sleeping...\n",
		(get_time() - philo->monitor->simu_start), philo->id);
	while (done_time != philo->time_to_sleep)
	{
		usleep(1000);
		done_time += 1;
		if (philo->monitor->dead == 1)
		{
			// printf("philo %d quit...:(\n", philo->id);
			return (0);
		}
	}
	return (1);
}

int	eating(t_philo *philo)
{
	size_t	done_time;

	done_time = 0;
	philo->last_meal = get_time();
	philo->meals_done++;
	printf("%ld philo %d is eating...\n",
		(get_time() - philo->monitor->simu_start), philo->id);
	while (done_time != philo->time_to_eat)
	{
		usleep(1000);
		done_time += 1;
		if (philo->monitor->dead == 1)
		{
			pthread_mutex_unlock(philo->left_fork_mutex);
			pthread_mutex_unlock(philo->right_fork_mutex);
			// printf("philo %d quit...:(\n", philo->id);
			return (0);
		}
	}
	if (philo->meals_done == philo->num_of_must_eat)
	{
		pthread_mutex_unlock(philo->left_fork_mutex);
		pthread_mutex_unlock(philo->right_fork_mutex);
		return (0);
	}
	return (1);
}

void    *routine_even(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->monitor->dead != 1)
	{
		if (get_time() - philo->last_meal >= philo->time_to_die)
		{
			philo->dead = 1;
			printf("%ld philo %d died\n",
				(get_time() - philo->monitor->simu_start), philo->id);
			break ;
		}
		think(philo);
		pthread_mutex_lock(philo->left_fork_mutex);
		printf("%ld philo %d has taken a fork...\n",
			get_time() - philo->monitor->simu_start, philo->id);
		pthread_mutex_lock(philo->right_fork_mutex);
		printf("%ld philo %d has taken a fork...\n",
			get_time() - philo->monitor->simu_start, philo->id);
		if (eating(philo) == 0)
			return (NULL);
		pthread_mutex_unlock(philo->left_fork_mutex);
		pthread_mutex_unlock(philo->right_fork_mutex);
		if (sleeping(philo) == 0)
			return (NULL);
	}
	return (NULL);
}

void    *routine_odd(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->monitor->dead != 1)
	{
		if (get_time() - philo->last_meal >= philo->time_to_die)
		{
			philo->dead = 1;
			printf("%ld philo %d died\n",
				(get_time() - philo->monitor->simu_start), philo->id);
			break ;
		}
		think(philo);
		pthread_mutex_lock(philo->right_fork_mutex);
		printf("%ld philo %d has taken a fork...\n",
			get_time() - philo->monitor->simu_start, philo->id);
		pthread_mutex_lock(philo->left_fork_mutex);
		printf("%ld philo %d has taken a fork...\n",
			get_time() - philo->monitor->simu_start, philo->id);
		if (eating(philo) == 0)
			return (NULL);
		pthread_mutex_unlock(philo->right_fork_mutex);
		pthread_mutex_unlock(philo->left_fork_mutex);
		if (sleeping(philo) == 0)
			return (NULL);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	int			i;
	int			num_philo;
	t_monitor	*monitor;
	int			meals_done_flag;

	monitor = (t_monitor *)arg;
	i = 0;
	meals_done_flag = 0;
	num_philo = monitor->philo_number;
	while (1)
	{
		i = 0;
		while (i < num_philo)
		{
			if (monitor->philo[i].dead == 1)
			{
				monitor->dead = 1;
				return (NULL);
			}
			if (monitor->philo[i].meals_done
				== monitor->philo[i].num_of_must_eat)
				meals_done_flag = 1;
			else if (monitor->philo[i].meals_done
				!= monitor->philo[i].num_of_must_eat)
				meals_done_flag = 0;
			if (meals_done_flag == 1 && i == num_philo - 1)
				return (NULL);
			i++;
		}
	}
}

int	trader(t_monitor *monitor)
{
	create_mutex(monitor);
	// printf("go creer thread\n");
	create_thread(monitor);
	// printf("go jointhread\n");
	thread_join(monitor);
	mutex_destroy(monitor);
	return (1);
}
