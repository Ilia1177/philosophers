/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:29:55 by npolack           #+#    #+#             */
/*   Updated: 2024/12/17 20:35:06 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_lstadd_back(t_philosoph **lst, t_philosoph *new)
{
	t_philosoph	*move;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		move = *lst;
		while (move->next)
			move = move->next;
		move->next = new;
	}
}

int	is_dead(t_philosoph *philo)
{
	if (philo->dead)
		return (1);
	return (0);
}

void	*live(void *philo)
{
	while (!is_dead(philo))
		eat(philo);
	pthread_exit(NULL);
}

void	take_a_nap(t_philosoph *philo)
{
	printf("philsoph %d is taking a nap\n", philo->id);
	philo->sleeping = 1;
	usleep(philo->time_to_sleep);
	philo->sleeping = 0;
	start_thinking(philo);
}

void	start_thinking(t_philosoph *philo)
{	
	printf("Philosoph %d start thinking\n", philo->id);
	philo->thinking = 1;
}

void	eat(t_philosoph *philo)
{
	int	*other_fork;

	other_fork = take_forks(philo);
	if (other_fork)
	{
		philo->thinking = 0;
		printf("philosoph %d start eating\n", philo->id);
		philo->eating = 1;
		usleep(philo->time_to_eat);
		philo->eating = 0;
		philo->fork = 1;
		*other_fork = 1;
		take_a_nap(philo);
	}
}

int	*take_forks(t_philosoph *philo)
{
	int	*philo_s_fork;

	philo_s_fork = NULL;
	if (philo->fork)
		philo->fork = 0;
	else
		return (NULL);
	if (philo->next && philo->next->fork)
	{
		philo_s_fork = &philo->next->fork;
		*philo_s_fork = 0;
	}
	else
		philo->fork = 1;
	return (philo_s_fork);
}
