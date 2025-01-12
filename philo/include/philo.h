/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:22:39 by npolack           #+#    #+#             */
/*   Updated: 2025/01/01 23:41:13 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

// ANSI color codes
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"

typedef struct s_philosoph
{
	pthread_mutex_t		*order;
	pthread_mutex_t		silverware;
	pthread_mutex_t		coffin;
	pthread_mutex_t		watch;
	pthread_mutex_t		stomach;
	struct timeval		*start;
	struct timeval		last_meal;
	pthread_t			itself;
	int					max_meal;
	int					full;
	int					id;
	int					eating;
	int					sleeping;
	int					thinking;
	int					time_to_sleep;
	int					time_to_eat;
	int					time_to_die;
	int					dead;
	struct s_philosoph	*next;
}	t_philosoph;

typedef struct	s_restaurant
{
	pthread_mutex_t order;
	struct timeval	start;
	int				max_meal;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				guest_nb;
	t_philosoph		*philo;
	pthread_t		table;
}	t_restaurant;

// fork.c
void		take_forks(t_philosoph *philo);
// common.c
void		announce(char *message, t_philosoph *philo);
int			ft_atoi(const char *nptr, int *result);
long long	look_at_the_time(struct timeval *start);
void		speak_poetry(char *poem, t_philosoph *philo);

// manager.c
void	kill_everyone(t_restaurant *inn);
void	supervise(t_restaurant *inn);
void	*manage_customers(void *restaurant);
int		all_alive(t_restaurant *inn);
int		is_dead(t_philosoph *philo);

// customers.c
void	*live(void *philosopher);
void	take_a_nap(t_philosoph *philo);
void	start_thinking(t_philosoph *philo);
void	eat(t_philosoph *philo);

// establishment.c

int		put_chairs_in_place(t_restaurant *inn);
void	welcome_customer(t_restaurant *inn, int id);
int		open_restaurant(t_restaurant *inn, int argc, char **argv);
int		dress_a_table(t_restaurant *inn);
int		close_establishment(t_restaurant *inn);

#endif
