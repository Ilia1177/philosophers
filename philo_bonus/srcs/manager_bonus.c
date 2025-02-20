/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:25:34 by npolack           #+#    #+#             */
/*   Updated: 2025/01/26 18:21:07 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	is_starving(t_philosoph *philo)
{
	int	life_situation;

	sem_wait(philo->starvation);
	life_situation = (philo->dead == 1);
	sem_post(philo->starvation);
	return (life_situation);
}

int	is_dead(t_philosoph *philo)
{
	long long	from_last_meal;

	if (is_starving(philo))
		return (1);
	sem_wait(philo->stomach);
	from_last_meal = look_at_the_time(&philo->last_meal);
	sem_post(philo->stomach);
	if (from_last_meal > philo->time_to_die * 1000)
	{
		speak_poetry("died", philo);
		return (1);
	}
	return (0);
}

int	get_staff_ready(t_restaurant *inn)
{
	if (pthread_create(&inn->waiter, NULL, &wait_for_full, inn))
		return (-1);
	if (pthread_create(&inn->security, NULL, &wait_for_all_dead, inn))
		return (-1);
	return (0);
}

void	wait_everybody(t_restaurant *inn)
{
	pthread_join(inn->security, NULL);
	pthread_join(inn->waiter, NULL);
	while (waitpid(-1, NULL, 0) > 0)
		;
}

sem_t	*call_lighthouse_name(char *name, int c, int id)
{
	sem_t	*lighthouse;
	int		i;
	int		divisor;
	char	digit;

	name[0] = '/';
	name[1] = 's';
	i = 2;
	divisor = 100;
	while (divisor > 0)
	{
		digit = (id / divisor) % 10;
		digit += '0';
		name[i++] = digit;
		divisor /= 10;
	}
	name[5] = c;
	name[6] = '\0';
	sem_unlink(name);
	lighthouse = sem_open(name, O_CREAT | O_EXCL, 0644, 1);
	return (lighthouse);
}
