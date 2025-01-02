/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:25:34 by npolack           #+#    #+#             */
/*   Updated: 2025/01/02 18:25:35 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	is_dead(t_philosoph *philo)
{
	long long	from_last_meal;

	sem_wait(philo->starvation);
	if (philo->dead)
	{
		sem_post(philo->starvation);
		return (1);
	}
	from_last_meal = look_at_the_time(&philo->last_meal);
	if (from_last_meal > philo->time_to_die * 1000)
	{
		speak_poetry("died", philo);
		philo->dead = 1;
		sem_post(philo->starvation);
		return (1);
	}
	sem_post(philo->starvation);
	return (0);
}
