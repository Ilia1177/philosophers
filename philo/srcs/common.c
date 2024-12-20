/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:29:55 by npolack           #+#    #+#             */
/*   Updated: 2024/12/20 01:54:21 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
void	announce(char *message, t_philosoph *philo)
{
		pthread_mutex_lock(philo->order);
		printf("%d %d %s\n", look_at_the_clock(philo), philo->id, message);
		pthread_mutex_unlock(philo->order);
}

void	kill_everyone(t_restaurant *inn)
{
	int	i;

	i = -1;
	while (++i < inn->guest_nb)
		inn->philo[i].dead = 1;
}

void	*manage_customers(void *restaurant)
{
	t_restaurant *inn;

	inn = restaurant;
	while (all_alive(inn))
		;
	kill_everyone(inn);
	pthread_mutex_lock(&inn->order);
	printf("%d Everyone killed\n", look_at_the_clock(&inn->philo[0]));
	pthread_mutex_unlock(&inn->order);
	return (NULL);
}

int	all_alive(t_restaurant *inn)
{
	int	i;

	i = -1;
	while (++i < inn->guest_nb)
		if (is_dead(&inn->philo[i]))
			return (0);
	return (1);
}

int	is_dead(t_philosoph *philo)
{
	struct timeval	current;
	suseconds_t		from_last_meal;

	gettimeofday(&current, NULL);
	from_last_meal = current.tv_usec - philo->last_meal.tv_usec;
	if (from_last_meal > philo->time_to_die)
	{
		pthread_mutex_lock(philo->order);
		printf("%d %d died because : %d > %d\n", look_at_the_clock(philo), philo->id, from_last_meal, philo->time_to_die); 
		pthread_mutex_unlock(philo->order);
		philo->dead = 1;
		return (1);
	}
	else
		return (0);
}

void	*live(void *philosopher)
{
	t_philosoph	*philo;

	philo = philosopher;
	while (philo->dead == 0)
		eat(philo);
	announce("bye bye", philo);
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
	if (philo->dead)
		return ;
	philo->sleeping = 1;
	announce("is sleeping", philo);
	usleep(philo->time_to_sleep);
	philo->sleeping = 0;
}

void	start_thinking(t_philosoph *philo)
{	
	if (philo->dead)
		return ;
	philo->thinking = 1;
	announce("is thinking", philo);
}

void		get_forks(t_philosoph *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->silverware);
		if (philo->dead)
		{
			pthread_mutex_unlock(&philo->silverware);
			return ;
		}
		announce("has taken a fork", philo);
		pthread_mutex_lock(&philo->next->silverware);
		if (philo->dead)
		{
			pthread_mutex_unlock(&philo->silverware);
			pthread_mutex_unlock(&philo->next->silverware);
			return ;
		}
		announce("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(&philo->next->silverware);
		if (philo->dead)
		{
			pthread_mutex_unlock(&philo->silverware);
			return ;
		}
		announce("has taken a fork", philo);
		pthread_mutex_lock(&philo->silverware);
		if (philo->dead)
		{
			pthread_mutex_unlock(&philo->silverware);
			pthread_mutex_unlock(&philo->next->silverware);
			return ;
		}
		announce("has taken a fork", philo);
	}
}

void	eat(t_philosoph *philo)
{
	get_forks(philo);
	if (philo->dead)
	{
		pthread_mutex_unlock(&philo->silverware);
		pthread_mutex_unlock(&philo->next->silverware);
		return ;
	}
	gettimeofday(&philo->last_meal, NULL);
	announce("is eating", philo);
	usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->silverware);
	pthread_mutex_unlock(&philo->next->silverware);
	take_a_nap(philo);
}

void	eat2(t_philosoph *philo)
{
	t_philosoph			*other;
	//suseconds_t		instant;

	other = take_forks(philo);
	if (other && !is_dead(philo))
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
		pthread_mutex_lock(&philo->silverware);
		pthread_mutex_lock(&other->silverware);
		philo->fork = 1;
		other->fork = 1;
		pthread_mutex_unlock(&philo->silverware); 
		pthread_mutex_unlock(&other->silverware); 
		take_a_nap(philo);
	}
	else if (is_dead(philo))
		exit(0);
	eat(philo);
}
