/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   establishment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:34:39 by npolack           #+#    #+#             */
/*   Updated: 2025/01/02 18:58:24 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	open_restaurant(t_restaurant *inn, int argc, char **argv)
{
	sem_close(inn->forks);
	sem_close(inn->speak);
	sem_close(inn->one_is_dead);
	sem_unlink("/silverware");
	sem_unlink("/speaker");
	sem_unlink("/death");
	sem_unlink("/A");
	sem_unlink("/B");
	sem_unlink("/C");
	sem_unlink("/D");
	sem_unlink("/E");

	gettimeofday(&inn->start, NULL);
	if (ft_atoi(argv[1], &inn->guest_nb) == -1)
		return (-1);
	if (ft_atoi(argv[2], &inn->time_to_die) == -1)
		return (-1);
	if (ft_atoi(argv[3], &inn->time_to_eat) == -1)
		return (-1);
	if (ft_atoi(argv[4], &inn->time_to_sleep) == -1)
		return (-1);
	if (argc == 5)
		inn->max_meal = -1;
	else if (argc == 6)
		if (ft_atoi(argv[5], &inn->max_meal) == -1)
			return (-1);
	inn->forks = sem_open("/silverware", O_CREAT | O_EXCL, 0644, inn->guest_nb);
	if (inn->forks == SEM_FAILED)
		return (emergency_exit(inn, "sem_open failed\n"));
	inn->speak = sem_open("/speaker", O_CREAT | O_EXCL, 0644, 1);
	if (inn->speak == SEM_FAILED)
    {
        sem_unlink("/silverware");
        return (emergency_exit(inn, "sem_open failed\n"));
    }
	inn->one_is_dead = sem_open("/death", O_CREAT | O_EXCL, 0644, 0);
	if (inn->one_is_dead == SEM_FAILED)
	{
		sem_unlink("/silverware");
		sem_unlink("/speaker");
		  return (emergency_exit(inn, "sem_open failed\n"));
	}
	//inn->all_full = sem_open("/full", O_CREAT | O_EXCL, 0644, 0);
	return (1);
}

int	close_establishment(t_restaurant *inn)
{
	free(inn->philo);
	sem_close(inn->forks);
	sem_close(inn->speak);
	sem_close(inn->one_is_dead);
//	sem_close(inn->all_full);
	sem_unlink("/silverware");
	sem_unlink("/speaker");
	sem_unlink("/death");
//	sem_unlink("/full");
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
	philo.start = &inn->start;
	gettimeofday(&philo.last_meal, NULL);
	return (philo);
}

void	*sit_at_the_table(void	*philosopher)
{
	t_philosoph	*philo;

	philo = philosopher;
	while (!is_starving(philo))
		eat(philo);
	return (NULL);
}

void	*watch(void *philosopher)
{
	t_philosoph	*philo;

	philo = philosopher;
	sem_wait(philo->one_dead);
	sem_wait(philo->starvation);
	philo->dead = 1;
	sem_post(philo->starvation);
	sem_post(philo->one_dead);
	return (NULL);
}

void	*manage(void *philosoph)
{
	t_philosoph	*philo;

	philo = philosoph;
	while (!is_dead(philo))
		;
	sem_post(philo->one_dead);
	sem_post(philo->one_dead);
	sem_post(philo->one_dead);
	sem_post(philo->one_dead);
	sem_post(philo->one_dead);
	return (NULL);
}

void	*look_for_full(void *restaurant)
{
	int	i;
	t_restaurant	*inn;

	inn = restaurant;
	i = 0;
	while (i < inn->guest_nb)
	{
		sem_wait(inn->all_full);
		i++;
	}
	// ....
	return (NULL);
}
int	child_process(t_philosoph *philo, int i)
{
	char		sem_name[3];
	pthread_t	undertaker;
	pthread_t	killer;

	sem_name[0] = '/';
	sem_name[1] = 'A' + i;
	sem_name[2] = '\0';
	philo->forks = sem_open("/silverware", 0);
	philo->speak = sem_open("/speaker", 0);
	philo->one_dead = sem_open("/death", 0);
	philo->starvation = sem_open(sem_name, O_CREAT | O_EXCL, 0644, 1);
	if (philo->starvation == SEM_FAILED)
		return (emergency_exit(NULL, "sem_open failed (starvation)\n"));
	pthread_create(&philo->itself, NULL, &sit_at_the_table, philo);
	pthread_create(&undertaker, NULL, &manage, philo);
	pthread_create(&killer, NULL, &watch, philo);
	pthread_join(philo->itself, NULL); // philosopher routine
	pthread_join(undertaker, NULL); // look for the death of philo[i]
	pthread_join(killer, NULL); // look for the death of another philo

	sem_close(philo->starvation);
	sem_close(philo->forks);
	sem_close(philo->speak);
	sem_close(philo->one_dead);
	sem_unlink(sem_name);
	return (0);
}

int	welcome_customers(t_restaurant *inn)
{
	int			i;

	inn->philo = malloc(sizeof(t_philosoph) * inn->guest_nb);
	i = 0;
	while (i < inn->guest_nb)
	{
		inn->philo[i] = new_customer(inn, i + 1);
		if (inn->philo[i].id == -1)
			return (-1);
		inn->philo[i].pid = fork();
		if (!inn->philo[i].pid)
		{
			child_process(&inn->philo[i], i);
			free(inn->philo);
			exit (0);
		}
		else if (inn->philo[i].pid > 0)
			i++;
		else
			return (emergency_exit(inn, "error fork"));
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (0);
}

/*
int	welcome_customers2(t_restaurant *inn)
{
	int			i;

	inn->philo = malloc(sizeof(t_philosoph) * inn->guest_nb);
	i = 0;
	while (i < inn->guest_nb)
	{
		inn->philo[i] = new_customer(inn, i + 1);
		inn->philo[i].pid = fork();
		if (!inn->philo[i].pid)
		{
			pthread_create(&inn->philo[i].itself, NULL, &sit_at_the_table, &inn->philo[i]);
			pthread_join(inn->philo[i].itself, NULL);
			free(inn->philo);
			exit(0);
		}
		else if (inn->philo[i].pid > 0)
			i++;
		else
		{
			free(inn->philo);
			return (emergency_exit(inn, "error fork"));
		}
	}
	//pthread_create(&inn->manager, NULL, &waitress, inn);
	//pthread_join(inn->manager, NULL);
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (0);
}*/
