/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   establishment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:34:39 by npolack           #+#    #+#             */
/*   Updated: 2025/02/28 16:19:16 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	put_chairs_in_place(t_restaurant *inn)
{
	int	i;

	inn->philo = malloc(sizeof(t_philosoph) * inn->guest_nb);
	if (!inn->philo)
		return (-1);
	if (inn->guest_nb > 1)
	{
		i = -1;
		while (++i < inn->guest_nb - 1)
			inn->philo[i].next = &inn->philo[i + 1];
		inn->philo[inn->guest_nb - 1].next = &inn->philo[0];
	}
	else if (inn->guest_nb == 1)
		inn->philo[0].next = NULL;
	i = -1;
	while (++i < inn->guest_nb)
		welcome_customer(inn, i);
	return (0);
}

void	welcome_customer(t_restaurant *inn, int id)
{
	inn->philo[id].coffin = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	inn->philo[id].watch = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	inn->philo[id].silverware = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	inn->philo[id].stomach = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	inn->philo[id].order = &inn->order;
	inn->philo[id].dead = 0;
	inn->philo[id].full = 0;
	inn->philo[id].max_meal = inn->max_meal;
	inn->philo[id].id = id + 1;
	inn->philo[id].time_to_sleep = inn->time_to_sleep;
	inn->philo[id].time_to_eat = inn->time_to_eat;
	inn->philo[id].time_to_die = inn->time_to_die;
	gettimeofday(&inn->philo[id].last_meal, NULL);
	gettimeofday(&inn->philo[id].start, NULL);
}

int	open_restaurant(t_restaurant *inn, int argc, char **argv)
{
	gettimeofday(&inn->start, NULL);
	inn->order = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	if (ft_atoi(argv[1], &inn->guest_nb) == -1 || inn->guest_nb <= 0)
		return (-1);
	if (ft_atoi(argv[2], &inn->time_to_die) == -1 || inn->time_to_die <= 0)
		return (-1);
	if (ft_atoi(argv[3], &inn->time_to_eat) == -1 || inn->time_to_eat <= 0)
		return (-1);
	if (ft_atoi(argv[4], &inn->time_to_sleep) == -1 || time_to_sleep <= 0)
		return (-1);
	if (argc == 6)
	{
		if (ft_atoi(argv[5], &inn->max_meal) == -1)
			return (-1);
	}
	else if (argc == 5)
		inn->max_meal = -1;
	if (put_chairs_in_place(inn) == -1)
		return (-1);
	return (1);
}

int	dress_a_table(t_restaurant *inn)
{
	int			i;
	pthread_t	*philo;

	i = -1;
	while (++i < inn->guest_nb)
	{
		usleep(inn->time_to_eat);
		philo = &inn->philo[i].itself;
		if (pthread_create(philo, NULL, &live, &inn->philo[i]))
		{
			close_establishment(inn, i, 1);
			return (-1);
		}
	}
	manage_customers(inn);
	return (1);
}

int	close_establishment(t_restaurant *inn, int i, int emergency)
{
	int	j;

	if (emergency)
	{
		kill_everyone(inn);
		while (--i >= 0)
			pthread_join(inn->philo[i].itself, NULL);
	}
	j = -1;
	while (++j < inn->guest_nb)
	{
		pthread_mutex_destroy(&inn->philo[j].coffin);
		pthread_mutex_destroy(&inn->philo[j].stomach);
		pthread_mutex_destroy(&inn->philo[j].silverware);
		pthread_mutex_destroy(&inn->philo[j].watch);
	}
	return (-1);
}
