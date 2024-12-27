/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilia <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:43:24 by ilia              #+#    #+#             */
/*   Updated: 2024/12/27 16:38:32 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <unistd.h>
# include <stdio.h>
#include <semaphore.h>
#include <limits.h>
#include <sys/time.h>
# include <pthread.h>
#include <stdlib.h>

typedef struct s_restaurant
{
	struct timeval	start;
	sem_t			*forks;
	sem_t			*speak;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				guest_nb;
	int				max_meal;
}	t_restaurant;

typedef	struct s_philosoph
{
	pthread_t		itself;
	int				id;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	sem_t			*forks;
	sem_t			*speak;
	int				max_meal;
	struct timeval	last_meal;
	struct timeval	*start;
	int				dead;
}	t_philosoph;

void		eat(t_philosoph *philo);
void		start_thinking(t_philosoph *philo);
void		take_a_nap(t_philosoph *philo);
void		*live(void *philosopher);
int			ft_atoi(const char *nptr, int *result);
void		speak_poetry(char *poem, t_philosoph *philo);
long long	look_at_the_time(struct timeval *start);
int			open_restaurant(t_restaurant *inn, int argc, char **argv);
int			is_dead(t_philosoph *philo);
int			close_establishment(t_restaurant *inn);
t_philosoph	*new_customer(t_restaurant *inn, int id);
void		*sit_at_the_table(void *philo);
int			welcome_customers(t_restaurant *inn);
#endif
