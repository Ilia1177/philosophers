/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:15:52 by npolack           #+#    #+#             */
/*   Updated: 2024/12/17 20:36:45 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	open_restaurant(t_restaurant *inn, char **argv)
{
	inn->guest_nb = ft_atoi(argv[1]);
	inn->time_to_die = ft_atoi(argv[2]);
	inn->time_to_die = ft_atoi(argv[3]);
	inn->time_to_sleep = ft_atoi(argv[4]);
	inn->max_meal = ft_atoi(argv[5]);
	inn->forks = malloc(sizeof(int *) * inn->guest_nb);
	inn->all_dead = 0;
	return (1);
}

int	dress_a_table(t_restaurant *inn)
{
	int			i;
	t_philosoph *link;

	inn->philo = malloc(sizeof(t_philosoph *) * inn->guest_nb);
	i = 0;
	while (i < inn->guest_nb)
	{
		inn->philo[i] = malloc(sizeof(t_philosoph));
		inn->philo[i].time_to_sleep = inn->time_to_die; 
		inn->philo[i].time_to_eat = inn->time_to_die;
		inn->philo[i].time_to_die = inn->time_to_sleep;
		inn->philo[i].id = i + 1;
		pthread_create(&inn->philo[i].itself, NULL, &live, &inn->philo[i]);
		link = philo[i];
		i++;
	}
	i = 0;
	while (i < inn->gust_nb - 1)
	{
		inn->philo[i].next = philo[i + 1];
		i++;
	}
	inn->philo[i].next = &inn->philo[0];
	return (1);
}

// s = pthread_create(&tinfo[tnum].thread_id, &attr, &thread_start, &tinfo[tnum])
//nb_of_philo 
//time_to_die
//time_to_eat
//time_to_sleep
//[number_of_times_each_philosopher_must_eat]
int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)envp;
	t_restaurant	inn;

	open_restaurant(&inn, argv);
	dress_a_table(&inn);
	return (0);
}
