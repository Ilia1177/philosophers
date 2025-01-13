/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilia <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 23:13:00 by ilia              #+#    #+#             */
/*   Updated: 2025/01/13 23:37:24 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	*sit_at_the_table(void	*philosopher)
{
	t_philosoph	*philo;

	philo = philosopher;
	while (!is_starving(philo))
		eat(philo);
	return (NULL);
}

void	*wait_for_dead(void *philosopher)
{
	t_philosoph	*philo;

	philo = philosopher;
	sem_wait(philo->one_dead);
	sem_post(philo->one_dead);
	sem_post(philo->one_dead);
	sem_wait(philo->starvation);
	philo->dead = 1;
	sem_post(philo->starvation);
	sem_post(philo->one_full);
	return (NULL);
}

void	*murder(void *philosoph)
{
	t_philosoph	*philo;

	philo = philosoph;
	while (!is_dead(philo))
		;
	return (NULL);
}

void	*wait_for_full(void *restaurant)
{
	int	i;
	t_restaurant	*inn;

	inn = restaurant;
	i = 0;
	while (i < inn->guest_nb)
	{
		sem_wait(inn->one_full);
		i++;
	}
	sem_post(inn->one_dead);
	return (NULL);
}
