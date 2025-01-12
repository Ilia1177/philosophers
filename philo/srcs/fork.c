/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:34:22 by npolack           #+#    #+#             */
/*   Updated: 2024/12/28 00:02:32 by ilia             ###   ########.fr       */
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
	if (!philo->next)
		return ;
	pthread_mutex_lock(&philo->silverware);
	pthread_mutex_lock(&philo->coffin);
	if (philo->dead)
	{
		pthread_mutex_unlock(&philo->coffin);
		pthread_mutex_unlock(&philo->silverware);
		return ;
	}
	pthread_mutex_unlock(&philo->coffin);
	speak_poetry("has taken a fork", philo);
	pthread_mutex_lock(&philo->next->silverware);
	pthread_mutex_lock(&philo->coffin);
	if (philo->dead)
	{
		pthread_mutex_unlock(&philo->coffin);
		pthread_mutex_unlock(&philo->silverware);
		pthread_mutex_unlock(&philo->next->silverware);
		return ;
	}
	pthread_mutex_unlock(&philo->coffin);
	speak_poetry("has taken a fork", philo);
}

static void	take_next_fork_first(t_philosoph *philo)
{
	if (!philo->next)
		return ;
	pthread_mutex_lock(&philo->next->silverware);
	pthread_mutex_lock(&philo->coffin);
	if (philo->dead)
	{
		pthread_mutex_unlock(&philo->coffin);
		pthread_mutex_unlock(&philo->silverware);
		return ;
	}
	pthread_mutex_unlock(&philo->coffin);
	speak_poetry("has taken a fork", philo);
	pthread_mutex_lock(&philo->silverware);
	pthread_mutex_lock(&philo->coffin);
	if (philo->dead)
	{
		pthread_mutex_unlock(&philo->coffin);
		pthread_mutex_unlock(&philo->silverware);
		pthread_mutex_unlock(&philo->next->silverware);
		return ;
	}
	pthread_mutex_unlock(&philo->coffin);
	speak_poetry("has taken a fork", philo);
}
