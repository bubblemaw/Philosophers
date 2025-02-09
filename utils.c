/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:05:46 by masase            #+#    #+#             */
/*   Updated: 2025/02/09 12:20:15 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	signe;
	int	resultat;

	resultat = 0;
	signe = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		signe *= -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		resultat *= 10;
		resultat = (str[i] - '0') + resultat;
		i++;
	}
	resultat *= signe;
	return (resultat);
}

size_t get_time(void)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	return ((time.tv_sec *1000000) + time.tv_usec);
}

int	tab_size(char **tab)
{
	int	i;
	
	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

