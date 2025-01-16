/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilia <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:43:24 by ilia              #+#    #+#             */
/*   Updated: 2025/01/16 11:10:10 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <unistd.h>
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
	sem_t			*starvation;
	sem_t			*quit;
	sem_t			*forks;
	sem_t			*speak;
	sem_t			*one_dead;
	sem_t			*one_full;
	pthread_t		itself;
	char			sem_name[6];
	int				dead;
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
	sem_t			*quit;
	t_philosoph		*philo;
	struct timeval	start;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				guest_nb;
	int				max_meal;
}	t_restaurant;

void		*wait_for_all_dead(void *restaurant);
int			light_on_sem(t_philosoph *philo, int id);
void		unlink_sem(void);
void		take_time(t_philosoph *philo, int time);
int			is_starving(t_philosoph *philo);
void		eat(t_philosoph *philo);
void		start_thinking(t_philosoph *philo);
void		take_a_nap(t_philosoph *philo);
void		*murder(void *philosopher);
void		*kill_everyone_and_leave(void *philosopher);
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
