/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilia <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 01:33:07 by ilia              #+#    #+#             */
/*   Updated: 2025/01/12 22:12:02 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	watch_on(t_philosoph *philo)
{
	pthread_t	leave;
	pthread_t	killer;
	
	pthread_create(&philo->itself, NULL, &sit_at_the_table, philo);
	pthread_create(&killer, NULL, &murder, philo); // kill the philo when starving 
	pthread_create(&leave, NULL, &look_for_dead, philo);
	pthread_join(philo->itself, NULL); // philosopher routine
	pthread_join(leave, NULL); // look for the death of philo[i]
	pthread_join(killer, NULL); // look for the death of another philo
	return (1);
}

int	customer_process(t_philosoph *philo)
{
	sem_post(philo->forks);
	watch_on(philo);
	sem_close(philo->starvation);
	sem_close(philo->forks);
	sem_close(philo->speak);
	sem_close(philo->one_dead);
	sem_unlink(philo->sem_name);
	printf(">>>>> %d is finishing\n", philo->id);
	return (0);
}

int	welcome_customers(t_restaurant *inn)
{
	int			i;
	t_philosoph	philo;

	//pthread_t	waiter;
	printf(">>>>> welcome customers\n");
	//pthread_create(&waiter, NULL, &serve, inn);
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
			exit (0);
		}
		else if (philo.pid > 0)
			i++;
		else
			return (emergency_exit(inn, "error fork"));
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
 	printf(">>>> end welcoming\n");
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
	philo.sem_name[1] = 'A' + id - 1;
	philo.sem_name[2] = '\0';
	philo.forks = sem_open("/silverware", 0);
	philo.speak = sem_open("/speaker", 0);
	philo.one_dead = sem_open("/death", 0);
	philo.starvation = sem_open(philo.sem_name, O_CREAT | O_EXCL, 0644, 1);
	return (philo);
}
