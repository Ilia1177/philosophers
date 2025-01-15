/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilia <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 23:13:00 by ilia              #+#    #+#             */
/*   Updated: 2025/01/15 17:55:12 by npolack          ###   ########.fr       */
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
	sem_wait(philo->starvation);
	philo->dead = 1;
	sem_post(philo->starvation);
	sem_post(philo->one_dead);
	sem_post(philo->forks);
	sem_post(philo->forks);
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
	i = -1;
	while (++i < inn->guest_nb)
		sem_wait(inn->one_full);
	sem_wait(inn->speak);
	sem_post(inn->one_dead);
	printf("ALL FULL\n");
	usleep(1000000);
	//sem_post(inn->speak);
	return (NULL);
}
