/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:34:22 by npolack           #+#    #+#             */
/*   Updated: 2024/12/19 19:58:24 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	*take_other_fork(t_philosoph *philo);
int	*take_own_fork(t_philosoph *philo);
int	*take_forks(t_philosoph *philo);
int	*take_the_fork(int *fork, t_philosoph *philo);

int	*take_the_fork(int *fork, t_philosoph *philo)
{
	pthread_mutex_lock(philo->mutex);
	if (*fork == 1 && !is_dead(philo))
	{
		*fork = 0;
		pthread_mutex_unlock(philo->mutex);
		pthread_mutex_lock(philo->order);
		printf("%d %d has taken a fork\n", look_at_the_clock(philo), philo->id);
		pthread_mutex_unlock(philo->order);
	}
	else
	{
		pthread_mutex_unlock(philo->mutex);
		return (NULL);
	}
	return (fork);
}

int	*take_other_fork(t_philosoph *philo)
{
	int	*fork;

	fork = NULL;
	if (philo->next->fork)
		fork = take_the_fork(&philo->next->fork, philo);
	else
		while (!fork && !is_dead(philo))
			fork = take_the_fork(&philo->next->fork, philo);
	if (is_dead(philo))
		return (NULL);
	return (fork);
}

int	*take_own_fork(t_philosoph *philo)
{
	int	*fork;

	fork = NULL;
	if (philo->fork == 1)
		fork = take_the_fork(&philo->fork, philo);
	else
		while (!fork && !is_dead(philo))
			fork = take_the_fork(&philo->fork, philo);
	if (is_dead(philo))
		return (NULL);
	return (fork);
}

int	*take_forks(t_philosoph *philo)
{
	int	*fork;

	if (philo->id % 2 == 0)
	{
		fork = take_other_fork(philo);
		take_own_fork(philo);
	}
	else
	{
		take_own_fork(philo);
		fork = take_other_fork(philo);
	}
	return (fork);
}
