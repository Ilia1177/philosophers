/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:27:32 by npolack           #+#    #+#             */
/*   Updated: 2025/01/13 22:54:56 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_starving(t_philosoph *philo)
{
	pthread_mutex_lock(&philo->coffin);
	if (philo->dead)
	{
		pthread_mutex_unlock(&philo->coffin);
		return (1);
	}
	pthread_mutex_unlock(&philo->coffin);
	return (0);
}

void	*live(void *philosopher)
{
	t_philosoph	*philo;

	philo = philosopher;
	while (!is_starving(philo))
		eat(philo);
	return (NULL);
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
	if (!philo->next)
	{
		pthread_mutex_lock(&philo->silverware);
		speak_poetry("has taken a fork", philo);
		usleep(philo->time_to_die * 1000);
		pthread_mutex_unlock(&philo->silverware);
		return ;
	}
	take_forks(philo);
	if (is_starving(philo))
		return ;
	speak_poetry("is eating", philo);
	pthread_mutex_lock(&philo->stomach);
	if (philo->max_meal > 0)
		philo->max_meal--;
	pthread_mutex_unlock(&philo->stomach);
	pthread_mutex_lock(&philo->watch);
	gettimeofday(&philo->last_meal, NULL);
	pthread_mutex_unlock(&philo->watch);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->silverware);
	pthread_mutex_unlock(&philo->next->silverware);
	take_a_nap(philo);
}
