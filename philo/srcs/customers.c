/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:27:32 by npolack           #+#    #+#             */
/*   Updated: 2025/01/26 14:54:05 by npolack          ###   ########.fr       */
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
	if (!philo->next)
	{
		pthread_mutex_lock(&philo->silverware);
		speak_poetry("has taken a fork", philo);
		take_time(philo, philo->time_to_die);
		pthread_mutex_unlock(&philo->silverware);
		return ;
	}
	if (take_forks(philo) == 0)
		return ;
	else if (is_starving(philo))
	{
		pthread_mutex_unlock(&philo->next->silverware);
		pthread_mutex_unlock(&philo->silverware);
		return ;
	}
	speak_poetry("is eating", philo);
	digest_meal(philo);
	pthread_mutex_lock(&philo->watch);
	gettimeofday(&philo->last_meal, NULL);
	pthread_mutex_unlock(&philo->watch);
	take_time(philo, philo->time_to_eat);
	pthread_mutex_unlock(&philo->silverware);
	pthread_mutex_unlock(&philo->next->silverware);
	take_a_nap(philo);
}
