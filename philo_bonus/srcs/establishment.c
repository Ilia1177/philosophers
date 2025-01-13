/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   establishment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:34:39 by npolack           #+#    #+#             */
/*   Updated: 2025/01/13 11:29:39 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	open_restaurant(t_restaurant *inn, int argc, char **argv)
{
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
	inn->forks = sem_open("/silverware", O_CREAT | O_EXCL, 0644, 0);
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


void	*sit_at_the_table(void	*philosopher)
{
	t_philosoph	*philo;

	philo = philosopher;
	while (!is_starving(philo))
		eat(philo);
	return (NULL);
}

void	*look_for_dead(void *philosopher)
{
	t_philosoph	*philo;

	philo = philosopher;
	sem_wait(philo->one_dead);
	sem_post(philo->one_dead);
	sem_wait(philo->starvation);
	philo->dead = 1;
	sem_post(philo->starvation);
	return (NULL);
}

void	*murder(void *philosoph)
{
	t_philosoph	*philo;

	philo = philosoph;
	while (!is_dead(philo))
		;
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
