/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:29:55 by npolack           #+#    #+#             */
/*   Updated: 2024/12/13 12:06:10 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_a_nap(t_philosoph *philo, t_restaurant *table)
{
	printf("philsoph %d is taking a nap\n", philo->id);
	philo->sleeping = 1;
	usleep(table->time_to_sleep);
	philo->sleeping = 0;
	start_thinking(philo);
}

void	start_thinking(t_philosoph *philo)
{
	printf("Philosoph %d start thinking\n", philo->id);
	philo->thinking = 1;
}

void	eat(t_philosoph *philo, t_restaurant *table)
{
	int	*guest_fork;

	guest_fork = take_forks(philo);
	if (guest_fork)
	{
		philo->thinking = 0;
		printf("philosoph %d start eating\n", philo->id);
		philo->eating = 1;
		usleep(time_to_eat);
		philo->eating = 0;
		philo->fork = 1;
		*guest_fork = 1;
		take_a_nap(philo, table);
	}
}

int	*take_forks(t_philosoph *philo)
{
	int	*philo_s_fork;

	philo_s_fork = NULL;
	if (philo->fork)
		philo->fork = 0;
	else
		return (NULL);
	if (philo->next->fork)
	{
		philo_s_fork = &philo->next->fork;
		*philo_s_fork = 0;
	}
	else if (philo->prev->fork)
	{
		philo_s_fork = &philo->prev->fork;
		*philo_s_fork = 0;
	}
	else
		philo->fork = 1;
	return (philo_s_fork);
}



