/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:27:32 by npolack           #+#    #+#             */
/*   Updated: 2025/01/15 17:44:35 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	take_forks(t_philosoph *philo)
{
	sem_wait(philo->forks);
	if (is_starving(philo))
	{
		sem_post(philo->forks);
		return ;
	}
	speak_poetry("has taken a fork", philo);
	sem_wait(philo->forks);
	if (is_starving(philo))
	{
		sem_post(philo->forks);
		sem_post(philo->forks);
		return ;
	}
	speak_poetry("has taken a fork", philo);
}

void	take_a_nap(t_philosoph *philo)
{
	if (is_starving(philo))
		return ;
	speak_poetry("is sleeping", philo);
	take_time(philo, philo->time_to_sleep);
	start_thinking(philo);
}

void	start_thinking(t_philosoph *philo)
{
	if (is_starving(philo))
		return ;
	speak_poetry("is thinking", philo);
}

void	eat(t_philosoph *philo)
{
	take_forks(philo);
	if (is_starving(philo))
		return ;
	speak_poetry("is eating", philo);
	if (philo->max_meal > 0)
		philo->max_meal--;
	if (philo->max_meal == 0)
		sem_post(philo->one_full);
	gettimeofday(&philo->last_meal, NULL);
	take_time(philo, philo->time_to_eat);
	sem_post(philo->forks);
	sem_post(philo->forks);
	take_a_nap(philo);
}
