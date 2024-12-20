/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:27:32 by npolack           #+#    #+#             */
/*   Updated: 2024/12/20 17:03:46 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*live(void *philosopher)
{
	t_philosoph	*philo;

	philo = philosopher;
	while (philo->dead == 0)
		eat(philo);
	return (NULL);
}

void	take_a_nap(t_philosoph *philo)
{
	if (philo->dead)
		return ;
	philo->sleeping = 1;
	announce("\033[34mis sleeping", philo);
	usleep(philo->time_to_sleep * 1000);
	philo->sleeping = 0;
}

void	start_thinking(t_philosoph *philo)
{
	if (philo->dead)
		return ;
	philo->thinking = 1;
	announce("\033[34mis thinking", philo);
}

void	eat(t_philosoph *philo)
{
	if (philo->max_meal == 0)
		return ;
	take_forks(philo);
	if (philo->dead)
	{
		pthread_mutex_unlock(&philo->silverware);
		pthread_mutex_unlock(&philo->next->silverware);
		return ;
	}
	philo->max_meal--;
	gettimeofday(&philo->last_meal, NULL);
	announce("\033[34mis eating", philo);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->silverware);
	pthread_mutex_unlock(&philo->next->silverware);
	take_a_nap(philo);
}
