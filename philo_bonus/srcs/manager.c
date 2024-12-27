/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:25:34 by npolack           #+#    #+#             */
/*   Updated: 2024/12/26 21:26:25 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	is_dead(t_philosoph *philo)
{
	long long	from_last_meal;

	printf("dead");
	from_last_meal = look_at_the_time(&philo->last_meal);
	if (from_last_meal / 1000 > philo->time_to_die)
	{
		printf("IS dead");
		speak_poetry("died", philo);
		philo->dead = 1;
		return (1);
	}
	return (0);
}
