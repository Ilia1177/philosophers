/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:29:55 by npolack           #+#    #+#             */
/*   Updated: 2024/12/19 19:46:42 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*manage_customers(void *inn)
{
	while (!all_dead(inn))
		;
	printf("PHILO ALL DEAD \n");
	return (NULL);
}

int	all_dead(t_restaurant *inn)
{
	int	i;
	int	dead;

	dead = 1;
	i = -1;
	while (++i < inn->guest_nb)
	{
		if (inn->philo[i].dead == 1)
			continue ;
		if (!is_dead(&inn->philo[i]))
			dead = 0;
	}
	return (dead);
}

int	is_dead(t_philosoph *philo)
{
	struct timeval	current;
	suseconds_t		from_last_meal;

	pthread_mutex_lock(philo->coffin);
	if (philo->dead == 0)
	{
		gettimeofday(&current, NULL);
		from_last_meal = current.tv_usec - philo->last_meal.tv_usec;
		if (from_last_meal > philo->time_to_die)
		{
			philo->dead = 1;
			pthread_mutex_unlock(philo->coffin);
			pthread_mutex_lock(philo->order);
			printf("%d %d died because : %d > %d\n", look_at_the_clock(philo), philo->id, from_last_meal, philo->time_to_die); 
			pthread_mutex_unlock(philo->order);
			return (1);
		}
		else
		{
			pthread_mutex_unlock(philo->coffin);
			return (0);
		}
	}
	pthread_mutex_unlock(philo->coffin);
	return (1);
}

void	*live(void *philosopher)
{
	t_philosoph	*philo;

	philo = philosopher;
	while (!is_dead(philo))
		eat(philo);
	return (NULL);
}

suseconds_t	look_at_the_clock(t_philosoph *philo)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_usec - philo->start.tv_usec);
}

void	take_a_nap(t_philosoph *philo)
{
	//suseconds_t		instant;

	//instant = look_at_the_clock(philo);
	philo->sleeping = 1;
	pthread_mutex_lock(philo->order);
	printf("%d %d is sleeping\n", look_at_the_clock(philo), philo->id);
	pthread_mutex_unlock(philo->order);
	usleep(philo->time_to_sleep);
	philo->sleeping = 0;
	start_thinking(philo);
}

void	start_thinking(t_philosoph *philo)
{	
	//suseconds_t		instant;

	philo->thinking = 1;
	//instant = look_at_the_clock(philo);
	pthread_mutex_lock(philo->order);
	printf("%d %d is thinking\n", look_at_the_clock(philo), philo->id);
	pthread_mutex_unlock(philo->order);
}

void	eat(t_philosoph *philo)
{
	int				*other_fork;
	//suseconds_t		instant;

	other_fork = take_forks(philo);
	if (other_fork && !is_dead(philo))
	{
		gettimeofday(&philo->last_meal, NULL);
		philo->thinking = 0;
		philo->eating = 1;
		//instant = look_at_the_clock(philo);
		pthread_mutex_lock(philo->order);
		printf("%d %d is eating\n", look_at_the_clock(philo), philo->id);
		pthread_mutex_unlock(philo->order);
		usleep(philo->time_to_eat);
		philo->eating = 0;
		pthread_mutex_lock(philo->mutex);
		philo->fork = 1;
		*other_fork = 1;
		pthread_mutex_unlock(philo->mutex); 
		take_a_nap(philo);
	}
	else
		return ;
}
