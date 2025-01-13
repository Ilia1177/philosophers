/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:25:34 by npolack           #+#    #+#             */
/*   Updated: 2025/01/13 23:30:19 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	is_starving(t_philosoph *philo)
{
    int life_situation;

    sem_wait(philo->starvation);
    life_situation = (philo->dead == 1); 
	sem_post(philo->starvation);
    return (life_situation);
}

int	is_dead(t_philosoph *philo)
{
	long long	from_last_meal;

	if (is_starving(philo))
		return (1);
	from_last_meal = look_at_the_time(&philo->last_meal);
	if (from_last_meal > philo->time_to_die * 1000)
	{
		speak_poetry("died", philo);
		sem_post(philo->one_dead);
		//sem_wait(philo->starvation);
		//philo->dead = 1;
		//sem_post(philo->starvation);
		return (1);
	}
	return (0);
}
