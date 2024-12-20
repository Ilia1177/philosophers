/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:22:39 by npolack           #+#    #+#             */
/*   Updated: 2024/12/20 01:17:11 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philosoph
{
	pthread_mutex_t		*order;
	pthread_mutex_t		silverware;
	pthread_mutex_t		coffin;
	struct timeval		start;
	struct timeval		last_meal;
	pthread_t			itself;
	int					id;
	int					eating;
	int					sleeping;
	int					thinking;
	int					time_to_sleep;
	int					time_to_eat;
	int					time_to_die;
	int					dead;
	int					fork;
	struct s_philosoph	*next;
} t_philosoph;

typedef struct	s_restaurant
{
	pthread_mutex_t mutex;
	pthread_mutex_t order;
	pthread_mutex_t coffin;
	struct timeval	start;
	struct timeval	current_time;
	struct timeval	elapsed_time;
	long			time;
	int				max_meal;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				guest_nb;
	int				**forks;
	t_philosoph		*philo;
	pthread_t		table;
	int				all_dead;
} t_restaurant;

void	*live(void *philo);
int		ft_atoi(const char *nptr);
void	take_a_nap(t_philosoph *philo);
void	start_thinking(t_philosoph *philo);
void	eat(t_philosoph *philo);
t_philosoph	*take_forks(t_philosoph *philo);
int		all_alive(t_restaurant *inn);


int	is_dead(t_philosoph *philo);
void	*manage_customers(void *table);
suseconds_t look_at_the_clock(t_philosoph *philo);
#endif
