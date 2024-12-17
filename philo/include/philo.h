/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:22:39 by npolack           #+#    #+#             */
/*   Updated: 2024/12/17 20:07:35 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_philosoph
{
	pthread_t	itself;
	int			id;
	int			eating;
	int			sleeping;
	int			thinking;
	int			time_to_sleep;
	int			time_to_eat;
	int			time_to_die;
	int			dead;
	int			fork;
	struct s_philosoph *next;
} t_philosoph;

typedef struct	s_restaurant
{
	int			max_meal;
	int			time_to_sleep;
	int			time_to_eat;
	int			time_to_die;
	int			guest_nb;
	int			**forks;
	t_philosoph	*philo;
	pthread_t	table;
	int			all_dead;
} t_restaurant;

void	*live(void *philo);
int		ft_atoi(const char *nptr);
void	take_a_nap(t_philosoph *philo);
void	start_thinking(t_philosoph *philo);
void	eat(t_philosoph *philo);
int		*take_forks(t_philosoph *philo);

#endif
