/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilia <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 01:33:07 by ilia              #+#    #+#             */
/*   Updated: 2025/01/14 15:02:26 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	is_having_diner(t_philosoph *philo)
{
	pthread_t	leave;
	pthread_t	killer;

	if (pthread_create(&philo->itself, NULL, &sit_at_the_table, philo) == -1)
		return (-1);
	if (pthread_create(&killer, NULL, &murder, philo) == -1)
		return (-1);
	if (pthread_create(&leave, NULL, &wait_for_dead, philo) == -1)
		return (-1);
	if (pthread_join(philo->itself, NULL) == -1)
		return (-1);
	if (pthread_join(leave, NULL) == -1)
		return (-1);
	if (pthread_join(killer, NULL) == -1)
	   return (-1);
	return (0);
}

int	customer_process(t_philosoph *philo)
{
	if (is_having_diner(philo) == -1)
		return (-1);
	sem_close(philo->starvation);
	sem_close(philo->forks);
	sem_close(philo->speak);
	sem_close(philo->one_dead);
	sem_unlink(philo->sem_name);
	return (0);
}

int	welcome_customers(t_restaurant *inn)
{
	int			i;
	t_philosoph	philo;
	pthread_t	waiter;

	i = 0;
	while (i < inn->guest_nb)
	{
		philo.pid = fork();
		if (!philo.pid)
		{
			philo = new_customer(inn, i + 1);
			if (philo.id == -1)
				return (-1);
			if (customer_process(&philo) == -1)
				return (emergency_exit(NULL, "child fail\n"));
			sem_close(philo.starvation);
			sem_close(philo.forks);
			sem_close(philo.speak);
			sem_close(philo.one_dead);
			sem_close(philo.one_full);
			exit(0);
		}
		else if (philo.pid > 0)
			i++;
		else
			return (emergency_exit(inn, "error fork"));
	}
	pthread_create(&waiter, NULL, &wait_for_full, inn);
	pthread_join(waiter, NULL);
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (0);
}

t_philosoph	new_customer(t_restaurant *inn, int id)
{
	t_philosoph	philo;

	philo.full = 0;
	philo.dead = 0;
	philo.max_meal = inn->max_meal;
	philo.id = id;
	philo.time_to_sleep = inn->time_to_sleep;
	philo.time_to_eat = inn->time_to_eat;
	philo.time_to_die = inn->time_to_die;
	gettimeofday(&philo.last_meal, NULL);
	gettimeofday(&philo.start, NULL);
	philo.sem_name[0] = '/';
	philo.sem_name[1] = '\001' + id - 1;
	philo.sem_name[2] = '\0';
	philo.forks = sem_open("/silverware", 0);
	philo.speak = sem_open("/speaker", 0);
	philo.one_dead = sem_open("/death", 0);
	philo.one_full = sem_open("/full", 0);
	philo.starvation = sem_open(philo.sem_name, O_CREAT | O_EXCL, 0644, 1);
	sem_post(philo.forks);
	return (philo);
}
