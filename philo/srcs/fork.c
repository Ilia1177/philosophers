/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:34:22 by npolack           #+#    #+#             */
/*   Updated: 2025/02/28 14:43:47 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int		take_own_fork_first(t_philosoph *philo);

int	take_forks(t_philosoph *philo)
{
	if (take_own_fork_first(philo))
		return (1);
	return (0);
}

static int	take_own_fork_first(t_philosoph *philo)
{
	if (!philo->next)
		return (0);
	pthread_mutex_lock(&philo->silverware);
	if (is_starving(philo))
	{
		pthread_mutex_unlock(&philo->silverware);
		return (0);
	}
	speak_poetry("has taken a fork", philo);
	pthread_mutex_lock(&philo->next->silverware);
	if (is_starving(philo))
	{
		pthread_mutex_unlock(&philo->silverware);
		pthread_mutex_unlock(&philo->next->silverware);
		return (0);
	}
	speak_poetry("has taken a fork", philo);
	return (1);
}
