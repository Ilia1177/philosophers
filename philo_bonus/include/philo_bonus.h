/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilia <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:43:24 by ilia              #+#    #+#             */
/*   Updated: 2025/01/13 23:34:30 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <semaphore.h>
# include <limits.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <pthread.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <string.h>

typedef	struct s_philosoph
{
	char			sem_name[3];
	sem_t			*starvation;
	sem_t			*forks;
	sem_t			*speak;
	sem_t			*one_dead;
	sem_t			*one_full;
	int				dead;
	int				full;
	pthread_t		itself;
	int				id;
	pid_t			pid;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				max_meal;
	struct timeval	last_meal;
	struct timeval	start;
}	t_philosoph;

typedef struct s_restaurant
{
	sem_t			*one_full;
	sem_t			*one_dead;
	sem_t			*forks;
	sem_t			*speak;
	t_philosoph		*philo;
	pthread_t		manager;
	struct timeval	start;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				guest_nb;
	int				max_meal;
}	t_restaurant;

int	is_starving(t_philosoph *philo);
void		eat(t_philosoph *philo);
void		start_thinking(t_philosoph *philo);
void		take_a_nap(t_philosoph *philo);
void		*murder(void *philosopher);
void		*wait_for_dead(void *philosopher);
void		*wait_for_full(void *inn);
int			ft_atoi(const char *nptr, int *result);
void		speak_poetry(char *poem, t_philosoph *philo);
long long	look_at_the_time(struct timeval *start);
int			open_restaurant(t_restaurant *inn, int argc, char **argv);
int			customer_process(t_philosoph *philo);
int			is_dead(t_philosoph *philo);
int			close_establishment(t_restaurant *inn);
t_philosoph	new_customer(t_restaurant *inn, int id);
void		*sit_at_the_table(void *philo);
int			welcome_customers(t_restaurant *inn);
int			emergency_exit(t_restaurant *inn, char *message);
int			communication(int argc, char **argv);
#endif
