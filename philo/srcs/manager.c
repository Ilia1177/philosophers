/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:25:34 by npolack           #+#    #+#             */
/*   Updated: 2024/12/20 17:02:41 by npolack          ###   ########.fr       */
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
		inn->philo[i].dead = 1;
}

void	*manage_customers(void *restaurant)
{
	t_restaurant	*inn;

	inn = restaurant;
	while (all_alive(inn))
		;
	pthread_mutex_lock(&inn->order);
	kill_everyone(inn);
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
	if (from_last_meal > philo->time_to_die)
	{
		philo->dead = 1;
		announce("\033[31mdied", philo);
		return (1);
	}
	else
		return (0);
}
