/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:15:52 by npolack           #+#    #+#             */
/*   Updated: 2024/12/19 19:59:05 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	open_restaurant(t_restaurant *inn, char **argv)
{
	gettimeofday(&inn->start, NULL);
    pthread_mutex_init(&inn->mutex, NULL);
    pthread_mutex_init(&inn->order, NULL);
    pthread_mutex_init(&inn->coffin, NULL);
	inn->guest_nb = ft_atoi(argv[1]);
	inn->time_to_die = ft_atoi(argv[2]);
	inn->time_to_eat = ft_atoi(argv[3]);
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
		inn->philo[i].mutex = &inn->mutex;
		inn->philo[i].coffin = &inn->coffin;
		inn->philo[i].order = &inn->order;
		inn->forks[i] = &inn->philo[i].fork;
		inn->philo[i].fork = 1;
		inn->philo[i].id = i + 1;
		inn->philo[i].time_to_sleep = inn->time_to_sleep; 
		inn->philo[i].time_to_eat = inn->time_to_eat;
		inn->philo[i].time_to_die = inn->time_to_die;
		inn->philo[i].start = inn->start;
		inn->philo[i].last_meal	= inn->start;

//		gettimeofday(&inn->philo[i].last_meal, NULL);
//		gettimeofday(&inn->philo[i].start, NULL);
		pthread_create(&inn->philo[i].itself, NULL, &live, &inn->philo[i]);
	}
	return (1);
}

void	supervise(t_restaurant *inn)
{
	pthread_create(&inn->table, NULL, manage_customers, inn);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)envp;
	t_restaurant	inn;
	int	i;

	if (argc < 5)
	{
		printf("usage : philo <nb of philo> <time to die> <time to eat> [max meal]\n");
		return (0);
	}
	open_restaurant(&inn, argv);
	printf("%d restaurant opened\n", look_at_the_clock(&inn.philo[0]));
	dress_a_table(&inn);
	printf("%d table ready\n", look_at_the_clock(&inn.philo[0]));
	supervise(&inn);
	i = 0;
	while (i < inn.guest_nb)
	{
		pthread_join(inn.philo[i].itself, NULL);
		i++;
	}
	pthread_join(inn.table, NULL);
	return (0);
}
