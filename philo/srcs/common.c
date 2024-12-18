/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:29:55 by npolack           #+#    #+#             */
/*   Updated: 2024/12/18 18:40:19 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	look_for_dead(t_restaurant *inn)
{
	int	i;

	i = 0;
	while (i < inn->guest_nb)
	{
		if (inn->philo[i].dead == 0)
			return (0);
	}
	return (1);
}

int	is_dead(t_philosoph *philo)
{
	if (philo->dead)
		return (1);
	return (0);
}

void	*live(void *philo)
{
	while (!is_dead(philo))
		eat(philo);
	pthread_exit(NULL);
}

void	take_a_nap(t_philosoph *philo)
{
	philo->sleeping = 1;
	printf("%d is sleeping\n", philo->id);
	usleep(philo->time_to_sleep);
	philo->sleeping = 0;
	start_thinking(philo);
}

void	start_thinking(t_philosoph *philo)
{	
	philo->thinking = 1;
	printf("%d is thinking\n", philo->id);
}

void	eat(t_philosoph *philo)
{
	int	*other_fork;

	other_fork = take_forks(philo);
	if (other_fork)
	{
		philo->thinking = 0;
		philo->eating = 1;
		printf("%d is eating\n", philo->id);
		usleep(philo->time_to_eat);
		philo->eating = 0;
		philo->fork = 1;
		*other_fork = 1;
		take_a_nap(philo);
	}
}
