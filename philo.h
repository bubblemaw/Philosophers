/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:50:25 by maw               #+#    #+#             */
/*   Updated: 2025/05/08 17:05:45 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h> 
# define MILLISECONDS 1000

typedef struct s_monitor t_monitor;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_done;
	int				number_of_philo;
	int				dead;
	int				eating;
	int				think_flag;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_of_must_eat;
	pthread_mutex_t	*right_fork_mutex;
	pthread_mutex_t	*left_fork_mutex;
	t_monitor		*monitor;
}	t_philo;

typedef struct s_monitor
{
	pthread_t		thread;
	t_philo			*philo;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	dead_mutex;
	int				dead;
	int				philo_number;
	size_t			simu_start;
	pthread_mutex_t	eating_mutex;
	int				meals_counter_flag;
}	t_monitor;

int		ft_atoi(const char *str);
int		trader(t_monitor *monitor);
int		eating(t_philo *philo);
int		sleeping(t_philo *philo);
int		think(t_philo *philo);
int		create_mutex(t_monitor *monitor);
int		create_thread(t_monitor *monitor);
int		thread_join(t_monitor *monitor);
int		mutex_destroy(t_monitor *monitor);
void	*routine_last(void *arg);
void	*routine(void *arg);
void	*monitor_routine(void *arg);
int		meals_manager(t_monitor *monitor, int *meals_done_flag, int i);
size_t	get_time(void);
int		philo_init(t_monitor *monitor, char **tab, int argc);
int		print_philo(t_monitor *monitor);

#endif
