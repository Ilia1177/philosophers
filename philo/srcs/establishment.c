/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   establishment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:34:39 by npolack           #+#    #+#             */
/*   Updated: 2024/12/20 16:39:31 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	put_chairs_in_place(t_restaurant *inn)
{
	int	i;

	inn->philo = malloc(sizeof(t_philosoph) * inn->guest_nb);
	i = -1;
	while (++i < inn->guest_nb - 1)
		inn->philo[i].next = &inn->philo[i + 1];
	inn->philo[inn->guest_nb - 1].next = &inn->philo[0];
	i = -1;
	while (++i < inn->guest_nb)
		welcome_customer(inn, i);
}

void	welcome_customer(t_restaurant *inn, int id)
{
	pthread_mutex_init(&inn->philo[id].silverware, NULL);
	inn->philo[id].order = &inn->order;
	inn->philo[id].dead = 0;
	inn->philo[id].max_meal = inn->max_meal;
	inn->philo[id].id = id + 1;
	inn->philo[id].time_to_sleep = inn->time_to_sleep;
	inn->philo[id].time_to_eat = inn->time_to_eat;
	inn->philo[id].time_to_die = inn->time_to_die;
	gettimeofday(&inn->philo[id].last_meal, NULL);
	inn->philo[id].start = &inn->start;
}

int	open_restaurant(t_restaurant *inn, int argc, char **argv)
{
	gettimeofday(&inn->start, NULL);
	pthread_mutex_init(&inn->order, NULL);
	inn->guest_nb = ft_atoi(argv[1]);
	inn->time_to_die = ft_atoi(argv[2]);
	inn->time_to_eat = ft_atoi(argv[3]);
	inn->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		inn->max_meal = ft_atoi(argv[5]);
	else if (argc == 5)
		inn->max_meal = -1;
	put_chairs_in_place(inn);
	return (1);
}

int	dress_a_table(t_restaurant *inn)
{
	int			i;

	i = -1;
	while (++i < inn->guest_nb)
		pthread_create(&inn->philo[i].itself, NULL, &live, &inn->philo[i]);
	return (1);
}

int	close_establishment(t_restaurant *inn)
{
	int	i;

	i = 0;
	while (i < inn->guest_nb)
	{
		pthread_mutex_destroy(&inn->philo[i].silverware);
		i++;
	}
	free(inn->philo);
	pthread_mutex_destroy(&inn->order);
	return (0);
}
