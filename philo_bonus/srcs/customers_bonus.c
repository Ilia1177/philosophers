/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customers_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilia <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 01:33:07 by ilia              #+#    #+#             */
/*   Updated: 2025/01/26 19:00:43 by npolack          ###   ########.fr       */
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
	if (pthread_create(&leave, NULL, &kill_everyone_and_leave, philo) == -1)
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
	sem_unlink(philo->starv_n);
	sem_unlink(philo->stom_n);
	return (0);
}

void	close_customer_sem(t_philosoph *philo)
{
	sem_close(philo->stomach);
	sem_close(philo->starvation);
	sem_close(philo->forks);
	sem_close(philo->speak);
	sem_close(philo->one_dead);
	sem_close(philo->one_full);
}

int	welcome_customers(t_restaurant *inn)
{
	int			i;
	t_philosoph	philo;

	i = 0;
	while (i < inn->guest_nb)
	{
		philo.pid = fork();
		if (philo.pid == 0)
		{
			philo = new_customer(inn, i + 1);
			if (philo.id == -1)
				emergency_exit(inn, "fail making customers\n");
			if (customer_process(&philo) == -1)
				emergency_exit(inn, "child fail\n");
			close_customer_sem(&philo);
			exit(0);
		}
		else if (philo.pid > 0)
			i++;
		else
			return (emergency_exit(inn, "error fork"));
	}
	return (0);
}

t_philosoph	new_customer(t_restaurant *inn, int id)
{
	t_philosoph	philo;

	philo.dead = 0;
	philo.max_meal = inn->max_meal;
	philo.id = id;
	philo.time_to_sleep = inn->time_to_sleep;
	philo.time_to_eat = inn->time_to_eat;
	philo.time_to_die = inn->time_to_die;
	gettimeofday(&philo.last_meal, NULL);
	philo.start = inn->start;
	if (light_on_sem(&philo, id))
		philo.id = -1;
	return (philo);
}
