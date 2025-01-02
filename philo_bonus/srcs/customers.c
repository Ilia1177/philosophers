/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:27:32 by npolack           #+#    #+#             */
/*   Updated: 2025/01/02 17:48:12 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	is_starving(t_philosoph *philo)
{
	sem_wait(philo->starvation);
	if (philo->dead == 1)
	{
		sem_post(philo->starvation);
		return (1);
	}
	sem_post(philo->starvation);
	return (0);
}

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
	usleep(philo->time_to_sleep * 1000);
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
	if (philo->max_meal > 0)
		philo->max_meal--;
	gettimeofday(&philo->last_meal, NULL);
	speak_poetry("is eating", philo);
	usleep(philo->time_to_eat * 1000);
	sem_post(philo->forks);
	sem_post(philo->forks);
	take_a_nap(philo);
}
