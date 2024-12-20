/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:34:22 by npolack           #+#    #+#             */
/*   Updated: 2024/12/20 17:04:02 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void		take_next_fork_first(t_philosoph *philo);
static void		take_own_fork_first(t_philosoph *philo);

void	take_forks(t_philosoph *philo)
{
	if (philo->id % 2 == 0)
		take_own_fork_first(philo);
	else
		take_next_fork_first(philo);
}

static void	take_own_fork_first(t_philosoph *philo)
{
	pthread_mutex_lock(&philo->silverware);
	if (philo->dead)
	{
		pthread_mutex_unlock(&philo->silverware);
		return ;
	}
	announce("\033[34mhas taken a fork", philo);
	pthread_mutex_lock(&philo->next->silverware);
	if (philo->dead)
	{
		pthread_mutex_unlock(&philo->silverware);
		pthread_mutex_unlock(&philo->next->silverware);
		return ;
	}
	announce("\033[34mhas taken a fork", philo);
}

static void	take_next_fork_first(t_philosoph *philo)
{
	pthread_mutex_lock(&philo->next->silverware);
	if (philo->dead)
	{
		pthread_mutex_unlock(&philo->silverware);
		return ;
	}
	announce("\033[34mhas taken a fork", philo);
	pthread_mutex_lock(&philo->silverware);
	if (philo->dead)
	{
		pthread_mutex_unlock(&philo->silverware);
		pthread_mutex_unlock(&philo->next->silverware);
		return ;
	}
	announce("\033[34mhas taken a fork", philo);
}
