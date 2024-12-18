/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:15:52 by npolack           #+#    #+#             */
/*   Updated: 2024/12/18 19:00:48 by npolack          ###   ########.fr       */
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
	inn->all_dead = 0;
	return (1);
}

int	dress_a_table(t_restaurant *inn)
{
	int			i;

	inn->philo = malloc(sizeof(t_philosoph) * inn->guest_nb);
	inn->forks = malloc(sizeof(int *) * inn->guest_nb);
	i = -1;
	while (++i < inn->guest_nb - 1)
		inn->philo[i].next = &inn->philo[i + 1];
	inn->philo[inn->guest_nb - 1].next = &inn->philo[0];
	i = -1;
	while (++i < inn->guest_nb)
	{
		inn->forks[i] = &inn->philo[i].fork;
		inn->philo[i].fork = 1;
		inn->philo[i].id = i + 1;
		inn->philo[i].time_to_sleep = inn->time_to_die; 
		inn->philo[i].time_to_eat = inn->time_to_die;
		inn->philo[i].time_to_die = inn->time_to_sleep;
		pthread_create(&inn->philo[i].itself, NULL, &live, &inn->philo[i]);
	}
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
	struct timeval start;
	struct timeval current;
	long elapse;
	t_restaurant	inn;
	int	i;

    gettimeofday(&start, NULL);
	elapse = (current.tv_sec - start.tv_sec) * 1000 + (current.tv_usec - start.tv_usec) / 1000;

	printf("%ld\n", elapse);
	return (0);
	open_restaurant(&inn, argv);
	dress_a_table(&inn);
	i = 0;
	while (i < inn.guest_nb)
	{
		pthread_join(inn.philo[i].itself, NULL);
		i++;
	}
	return (0);
}
