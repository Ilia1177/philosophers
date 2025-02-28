/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customers_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilia <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 01:33:07 by ilia              #+#    #+#             */
/*   Updated: 2025/02/28 10:25:06 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	is_having_diner(t_philosoph *philo)
{
	pthread_t	leave;
	pthread_t	killer;

	if (pthread_create(&philo->itself, NULL, &sit_at_the_table, philo))
		sem_post(philo->quit);
	if (pthread_create(&killer, NULL, &murder, philo))
		sem_post(philo->quit);
	if (pthread_create(&leave, NULL, &kill_everyone_and_leave, philo))
		sem_post(philo->quit);
	pthread_join(philo->itself, NULL);
	pthread_join(leave, NULL);
	pthread_join(killer, NULL);
	return (0);
}

int	customer_process(t_philosoph *philo)
{
	is_having_diner(philo);
	close_customer_sem(philo);
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
		if (i % 2 == 0)
			usleep(350);
		philo.pid = fork();
		if (philo.pid == 0)
		{
			philo = new_customer(inn, i + 1);
			if (philo.id != -1)
				customer_process(&philo);
			else
				emergency_exit(inn, &philo, "fail making customers\n");
			close_establishment(inn);
			exit(0);
		}
		else if (philo.pid > 0)
			i++;
		else
			return (-1);
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
	gettimeofday(&philo.start, NULL);
	if (light_on_sem(&philo, id))
	{
		close_customer_sem(&philo);
		philo.id = -1;
	}
	return (philo);
}
