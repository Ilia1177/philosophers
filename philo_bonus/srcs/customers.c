/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:27:32 by npolack           #+#    #+#             */
/*   Updated: 2024/12/26 21:25:25 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"
void	take_forks(t_philosoph *philo)
{
	printf("take forks\n");
	sem_wait(philo->forks);
	if (is_dead(philo))
	{
		sem_post(philo->forks);
		return ;
	}
	speak_poetry("has taken a fork", philo);
	sem_wait(philo->forks);
	if (is_dead(philo))
	{
		sem_post(philo->forks);
		sem_post(philo->forks);
		return ;
	}
	speak_poetry("has taken a fork", philo);

}
void	take_a_nap(t_philosoph *philo)
{
	printf("sleep\n");
	if (is_dead(philo))
	{
		return ;
	}
	speak_poetry("is sleeping", philo);
	usleep(philo->time_to_sleep * 1000);
	start_thinking(philo);
}

void	start_thinking(t_philosoph *philo)
{
	printf("think\n");
	if (is_dead(philo))
	{
		return ;
	}
	speak_poetry("is thinking", philo);
}

void	eat(t_philosoph *philo)
{
	printf("eat\n");
	if (philo->max_meal == 0)
		return ;
	take_forks(philo);
	if (is_dead(philo))
	{
		return ;
	}
	philo->max_meal--;
	gettimeofday(&philo->last_meal, NULL);
	speak_poetry("is eating", philo);
	usleep(philo->time_to_eat * 1000);
	sem_post(philo->forks);
	sem_post(philo->forks);
	take_a_nap(philo);
}
