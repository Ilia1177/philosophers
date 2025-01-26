/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilia <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 23:13:00 by ilia              #+#    #+#             */
/*   Updated: 2025/01/26 19:11:29 by npolack          ###   ########.fr       */
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

void	*kill_everyone_and_leave(void *philosopher)
{
	t_philosoph	*philo;

	philo = philosopher;
	sem_wait(philo->quit);
	sem_post(philo->quit);
	sem_wait(philo->starvation);
	philo->dead = 1;
	sem_post(philo->starvation);
	sem_post(philo->one_dead);
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
	int				i;
	t_restaurant	*inn;

	inn = restaurant;
	i = -1;
	while (++i < inn->guest_nb)
		sem_wait(inn->one_full);
	sem_wait(inn->speak);
	sem_post(inn->quit);
	return (NULL);
}

void	*wait_for_all_dead(void *restaurant)
{
	t_restaurant	*inn;
	int				i;

	inn = restaurant;
	i = -1;
	while (++i < inn->guest_nb)
		sem_wait(inn->one_dead);
	i = -1;
	while (++i < inn->guest_nb)
		sem_post(inn->forks);
	i = -1;
	while (++i < inn->guest_nb)
		sem_post(inn->one_full);
	usleep(500000);
	sem_post(inn->speak);
	sem_post(inn->speak);
	return (NULL);
}
