/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:58:56 by masase            #+#    #+#             */
/*   Updated: 2025/05/09 12:30:50 by masase           ###   ########.fr       */
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
	while (philo->time_to_eat >= current_time - start_time)
	{
		usleep(500);
		current_time = get_time();
		// printf("%ld\n", current_time - start_time);
		if (philo->monitor->dead == 1)
		{
			pthread_mutex_unlock(philo->left_fork_mutex);
			pthread_mutex_unlock(philo->right_fork_mutex);
			return (0);
		}
	}
	pthread_mutex_lock(&philo->monitor->eating_mutex);
	philo->last_meal = get_time();
	philo->eating = 0;
	pthread_mutex_unlock(&philo->monitor->eating_mutex);
	philo->meals_done++;
	philo->think_flag = 0;
	pthread_mutex_unlock(philo->left_fork_mutex);
	pthread_mutex_unlock(philo->right_fork_mutex);
	return (1);
}

void    *routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->monitor->dead != 1)
	{
		// if (philo->think_flag == 0)
			think(philo);
			if (philo->id % 2 == 0)
				usleep(1000);
		// if (philo->left_fork_mutex)
		// {
			pthread_mutex_lock(philo->left_fork_mutex);
			if (philo->monitor->dead == 1)
			{
				pthread_mutex_unlock(philo->left_fork_mutex);
				break ;
			}
			printf("%ld %d has taken a fork...\n",
				get_time() - philo->monitor->simu_start, philo->id);
		// }
		// if (philo->right_fork_mutex)
		// {
			pthread_mutex_lock(philo->right_fork_mutex);
			if (philo->monitor->dead == 1)
			{
				pthread_mutex_unlock(philo->left_fork_mutex);
				pthread_mutex_unlock(philo->right_fork_mutex);
				break ;
			}
			printf("%ld %d has taken a fork...\n",
				get_time() - philo->monitor->simu_start, philo->id);
		// }
		// else 
		// 	continue ;
		if (eating(philo) == 0)
			break ;
		if (sleeping(philo) == 0)
			break ;
	}
	if (philo->dead == 1)
	{
		printf("%ld %d died\n",
			(get_time() - philo->monitor->simu_start), philo->id);
		printf("c'est monitor qui fait quitter\n");
	}
	return (NULL);
}

void    *routine_last(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->monitor->dead != 1)
	{
		// if (philo->think_flag == 0)
			think(philo);
		// if (philo->right_fork_mutex)
		// {
			pthread_mutex_lock(philo->right_fork_mutex);
			if (philo->monitor->dead == 1)
			{
				pthread_mutex_unlock(philo->right_fork_mutex);
				break ;
			}
			printf("%ld %d has taken a fork...\n",
				get_time() - philo->monitor->simu_start, philo->id);
		// }
		// if (philo->left_fork_mutex)
		// {
			pthread_mutex_lock(philo->left_fork_mutex);
			if (philo->monitor->dead == 1)
			{
				pthread_mutex_unlock(philo->left_fork_mutex);
				pthread_mutex_unlock(philo->right_fork_mutex);
				break ;
			}
			printf("%ld %d has taken a fork...\n",
				get_time() - philo->monitor->simu_start, philo->id);
		// }
		// else
		// 	continue ;
		if (eating(philo) == 0)
			break ;
		if (sleeping(philo) == 0)
			break ;
	}
	if (philo->dead == 1)
	{
		printf("%ld %d died\n",
			(get_time() - philo->monitor->simu_start), philo->id);
		printf("c'est monitor qui fait quitter\n");
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	int			i;
	int			num_philo;
	size_t		current_time;
	t_monitor	*monitor;
	int			meals_done_flag;

	monitor = (t_monitor *)arg;
	i = 0;
	meals_done_flag = 0;
	num_philo = monitor->philo_number;
	while (1)
	{
		i = 0;
		usleep(500);
		while (i < num_philo)
		{
			pthread_mutex_lock(&monitor->eating_mutex);
			if (current_time - monitor->philo[i].last_meal
				> monitor->philo[i].time_to_die
				&& monitor->philo[i].eating == 0)
			{
				printf("%ld\n", current_time - monitor->philo[i].last_meal);
				monitor->philo[i].dead = 1;
				monitor->dead = 1;
				pthread_mutex_unlock(monitor->philo[i].left_fork_mutex);
				pthread_mutex_unlock(monitor->philo[i].right_fork_mutex);
				// printf("%ld %d died\n",
				// 	(get_time() - monitor->simu_start), monitor->philo[i].id);
				// printf("c'est monitor qui fait quitter\n");
				pthread_mutex_unlock(&monitor->eating_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&monitor->eating_mutex);
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
