/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:25:34 by npolack           #+#    #+#             */
/*   Updated: 2024/12/22 23:11:50 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	supervise(t_restaurant *inn)
{
	pthread_create(&inn->table, NULL, &manage_customers, inn);
}

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

void	*manage_customers(void *restaurant)
{
	t_restaurant	*inn;

	inn = restaurant;
	while (all_alive(inn))
		;
	kill_everyone(inn);
	pthread_mutex_unlock(&inn->order);
	return (NULL);
}

int	all_alive(t_restaurant *inn)
{
	int	i;

	i = -1;
	while (++i < inn->guest_nb)
		if (inn->philo[i].id && is_dead(&inn->philo[i]))
			return (0);
	return (1);
}

int	is_dead(t_philosoph *philo)
{
	long long	from_last_meal;

	from_last_meal = look_at_the_time(&philo->last_meal);
	if (from_last_meal / 1000 > philo->time_to_die)
	{
		speak_poetry("died", philo);
		pthread_mutex_lock(philo->order);
		pthread_mutex_lock(&philo->coffin);
		philo->dead = 1;
		pthread_mutex_unlock(&philo->coffin);
		return (1);
	}
	return (0);
}
