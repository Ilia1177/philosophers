/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:25:34 by npolack           #+#    #+#             */
/*   Updated: 2025/01/16 14:01:31 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	kill_everyone(t_restaurant *inn)
{
	int	i;

	i = -1;
	while (++i < inn->guest_nb)
	{
		pthread_mutex_lock(&inn->philo[i].coffin);
		inn->philo[i].dead = 1;
		pthread_mutex_unlock(&inn->philo[i].coffin);
	}
}

int	all_full(t_restaurant *inn)
{
	int	i;

	if (inn->max_meal == -1)
		return (0);
	i = -1;
	while (++i < inn->guest_nb)
	{
		pthread_mutex_lock(&inn->philo[i].stomach);
		if (inn->philo[i].max_meal > 0)
		{
			pthread_mutex_unlock(&inn->philo[i].stomach);
			return (0);
		}
		pthread_mutex_unlock(&inn->philo[i].stomach);
	}
	return (1);
}

void	*manage_customers(void *restaurant)
{
	t_restaurant	*inn;

	inn = restaurant;
	while (all_alive(inn) && all_full(inn) == 0)
		;
	kill_everyone(inn);
	return (NULL);
}

int	all_alive(t_restaurant *inn)
{
	int	i;

	i = -1;
	while (++i < inn->guest_nb)
		if (is_dead(&inn->philo[i]))
			return (0);
	return (1);
}

int	is_dead(t_philosoph *philo)
{
	long long	from_last_meal;

	pthread_mutex_lock(&philo->watch);
	from_last_meal = look_at_the_time(&philo->last_meal);
	pthread_mutex_unlock(&philo->watch);
	if (from_last_meal > philo->time_to_die * 1000)
	{
		speak_poetry("died", philo);
		pthread_mutex_lock(&philo->coffin);
		philo->dead = 1;
		pthread_mutex_unlock(&philo->coffin);
		return (1);
	}
	return (0);
}
