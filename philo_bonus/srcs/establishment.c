/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   establishment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:34:39 by npolack           #+#    #+#             */
/*   Updated: 2024/12/27 16:38:27 by ilia             ###   ########.fr       */
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
	if (argc == 6)
	{
		if (ft_atoi(argv[5], &inn->max_meal) == -1)
			return (-1);
	}
	else if (argc == 5)
		inn->max_meal = -1;
	inn->forks = sem_open("/silverware", O_CREAT | O_EXCL, 0600, inn->guest_nb);
	inn->speak = sem_open("/speaker", O_CREAT | O_EXCL, 0600, 1);
	return (1);
}

int	close_establishment(t_restaurant *inn)
{
	(void)inn;

	sem_unlink("/silverware");
	sem_unlink("/forks");
	return (0);
}

t_philosoph	*new_customer(t_restaurant *inn, int id)
{
	t_philosoph	*philo;

	philo = malloc(sizeof(t_philosoph));
	philo->dead = 0;
	philo->max_meal = inn->max_meal;
	philo->id = id;
	philo->time_to_sleep = inn->time_to_sleep;
	philo->time_to_eat = inn->time_to_eat;
	philo->time_to_die = inn->time_to_die;
	philo->start = &inn->start;
	gettimeofday(&philo->last_meal, NULL);

	philo->forks = inn->forks;
	philo->speak = inn->speak;
	return (philo);
}

void	*sit_at_the_table(void	*philosopher)
{
	t_philosoph	*philo;

	printf("sit\n");
	philo = philosopher;
	while (!is_dead(philo))
		eat(philo);
	free(philo);
	return (NULL);
}

int	welcome_customers(t_restaurant *inn)
{
	int			pid;
	int			i;
	t_philosoph	*philo;

	i = 0;
	while (i < inn->guest_nb)
	{
		philo = new_customer(inn, i + 1);
		pid = fork();
		if (!pid)
		{
			//sit_at_the_table(philo);
			pthread_create(&philo->itself, NULL, &sit_at_the_table, philo);
			pthread_join(philo->itself, NULL);
			exit (0);
		}
		i++;
	}
	exit (0);
}
