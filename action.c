/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:10:50 by maw               #+#    #+#             */
/*   Updated: 2025/05/08 17:17:59 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int try_get_fork(t_philo *philo)
{
	size_t	start_time;
	size_t	current_time;

	start_time = get_time();
	current_time = get_time();
	while (50 > current_time - start_time)
	{
		current_time = get_time();
		pthread_mutex_lock(philo->left_fork_mutex);
	}
	return (0);
}