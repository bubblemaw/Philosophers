/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:50:25 by maw               #+#    #+#             */
/*   Updated: 2025/01/31 17:02:01 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# define MILLISECONDS 1000

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	int			meals_done;
	int			number_of_philo;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int			num_of_must_eat;
	pthread_mutex_t *fork_mutex;

}	t_philo;

typedef struct s_monitor
{

	t_philo *philo;
	pthread_mutex_t *eat_mutex;
}	t_monitor;

int	ft_atoi(const char *str);
int	trader(t_monitor *monitor);
void    *routine(void *arg);
int eating(t_philo *philo);
int sleeping(t_philo *philo);
int think(t_philo *philo);


#endif
