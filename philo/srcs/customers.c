/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:27:32 by npolack           #+#    #+#             */
/*   Updated: 2024/12/22 22:54:39 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*live(void *philosopher)
{
	t_philosoph	*philo;

	philo = philosopher;
	pthread_mutex_lock(&philo->coffin);
	while (philo->dead == 0)
	{
		pthread_mutex_unlock(&philo->coffin);
		eat(philo);
		pthread_mutex_lock(&philo->coffin);
	}
	pthread_mutex_unlock(&philo->coffin);
	return (NULL);
}

void	take_a_nap(t_philosoph *philo)
{
	pthread_mutex_lock(&philo->coffin);
	if (philo->dead)
	{
		pthread_mutex_unlock(&philo->coffin);
		return ;
	}
	pthread_mutex_unlock(&philo->coffin);
	speak_poetry("is sleeping", philo);
	usleep(philo->time_to_sleep * 1000);
	start_thinking(philo);
}

void	start_thinking(t_philosoph *philo)
{
	pthread_mutex_lock(&philo->coffin);
	if (philo->dead)
	{
		pthread_mutex_unlock(&philo->coffin);
		return ;
	}
	pthread_mutex_unlock(&philo->coffin);
	speak_poetry("is thinking", philo);
}

void	eat(t_philosoph *philo)
{
	if (philo->max_meal == 0)
		return ;
	take_forks(philo);
	pthread_mutex_lock(&philo->coffin);
	if (philo->dead)
	{
		pthread_mutex_unlock(&philo->coffin);
		pthread_mutex_unlock(&philo->silverware);
		pthread_mutex_unlock(&philo->next->silverware);
		return ;
	}
	pthread_mutex_unlock(&philo->coffin);
	philo->max_meal--;
	gettimeofday(&philo->last_meal, NULL);
	speak_poetry("is eating", philo);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->silverware);
	pthread_mutex_unlock(&philo->next->silverware);
	take_a_nap(philo);
}
