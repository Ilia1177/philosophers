/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:34:22 by npolack           #+#    #+#             */
/*   Updated: 2024/12/18 18:55:15 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	*take_other_fork(t_philosoph *philo);
int	*take_own_fork(t_philosoph *philo);
int	*take_forks(t_philosoph *philo);
int	*take_the_fork(int *fork);

int	*take_the_fork(int *fork)
{
	if (*fork == 1)
		*fork = 0;
	else
		return (NULL);
	return (fork);
}

int	*take_other_fork(t_philosoph *philo)
{
	int	*fork;

	fork = NULL;
	if (philo->next->fork)
		fork = take_the_fork(&philo->next->fork);
	else
		while (!fork)
			fork = take_the_fork(&philo->next->fork);
	printf("%d has taken a fork\n", philo->id);
	return (fork);
}

int	*take_own_fork(t_philosoph *philo)
{
	int	*fork;

	fork = NULL;
	if (philo->fork == 1)
		fork = take_the_fork(&philo->fork);
	else
		while (!fork)
			fork = take_the_fork(&philo->fork);
	printf("%d has taken a fork\n", philo->id);
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
