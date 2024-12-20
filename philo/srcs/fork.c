/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:34:22 by npolack           #+#    #+#             */
/*   Updated: 2024/12/20 00:12:36 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_philosoph	*take_other_fork(t_philosoph *philo);
int			*take_own_fork(t_philosoph *philo);
t_philosoph	*take_forks(t_philosoph *philo);
t_philosoph	*take_the_fork(t_philosoph *philo);

t_philosoph	*take_the_fork(t_philosoph *philo)
{
	pthread_mutex_lock(&philo->silverware);
	if (philo->fork == 1)
	{
		philo->fork = 0;
		pthread_mutex_unlock(&philo->silverware);
		pthread_mutex_lock(philo->order);
		printf("%d %d has taken a fork\n", look_at_the_clock(philo), philo->id);
		pthread_mutex_unlock(philo->order);
	}
	else
	{
		pthread_mutex_unlock(&philo->silverware);
		return (NULL);
	}
	return (philo);
}

t_philosoph	*take_forks(t_philosoph *philo)
{
	t_philosoph	*other;
	t_philosoph	*itself;

	itself = NULL;
	other = NULL;
	if (philo->id % 2 == 0)
	{
		while (!other)
			other = take_the_fork(philo->next);
		while (!itself)
			itself = take_the_fork(philo);
	}
	else
	{
		while (!itself)
			itself = take_the_fork(philo);
		while (!other)
			other = take_the_fork(philo->next);
	}
	return (other);
}
