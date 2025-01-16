/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   establishment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:34:39 by npolack           #+#    #+#             */
/*   Updated: 2025/01/16 14:05:46 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	unlink_sem(void)
{
	sem_unlink("/silverware");
	sem_unlink("/speaker");
	sem_unlink("/death");
	sem_unlink("/full");
	sem_unlink("/quit");
}

int	make_sem(t_restaurant *inn)
{
	unlink_sem();
	inn->forks = sem_open("/silverware", O_CREAT | O_EXCL, 0644, inn->guest_nb);
	if (inn->forks == SEM_FAILED)
		return (emergency_exit(inn, "sem_open failed\n"));
	inn->speak = sem_open("/speaker", O_CREAT | O_EXCL, 0644, 1);
	if (inn->speak == SEM_FAILED)
		return (emergency_exit(inn, "sem_open failed\n"));
	inn->one_dead = sem_open("/death", O_CREAT | O_EXCL, 0644, 0);
	if (inn->one_dead == SEM_FAILED)
		return (emergency_exit(inn, "sem_open failed\n"));
	inn->one_full = sem_open("/full", O_CREAT | O_EXCL, 0644, 0);
	if (inn->one_full == SEM_FAILED)
		return (emergency_exit(inn, "sem_open failed\n"));
	inn->quit = sem_open("/quit", O_CREAT | O_EXCL, 0644, 0);
	if (inn->quit == SEM_FAILED)
		return (emergency_exit(inn, "sem_open failed\n"));

	return (1);
}

int	open_restaurant(t_restaurant *inn, int argc, char **argv)
{
	gettimeofday(&inn->start, NULL);
	if (ft_atoi(argv[1], &inn->guest_nb) == -1)
		return (-1);
	if (ft_atoi(argv[2], &inn->time_to_die) == -1)
		return (-1);
	if (ft_atoi(argv[3], &inn->time_to_eat) == -1)
		return (-1);
	if (ft_atoi(argv[4], &inn->time_to_sleep) == -1)
		return (-1);
	if (argc == 5)
		inn->max_meal = -1;
	else if (argc == 6)
		if (ft_atoi(argv[5], &inn->max_meal) == -1)
			return (-1);
	if (make_sem(inn) == -1)
		return (-1);
	return (0);
}

int	close_establishment(t_restaurant *inn)
{
	sem_close(inn->forks);
	sem_close(inn->speak);
	sem_close(inn->one_dead);
	sem_close(inn->one_full);
	sem_close(inn->quit);
	unlink_sem();
	return (0);
}
