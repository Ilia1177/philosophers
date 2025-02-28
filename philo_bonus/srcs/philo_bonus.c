/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilia <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 18:05:14 by ilia              #+#    #+#             */
/*   Updated: 2025/02/12 15:54:57 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	emergency_exit(t_restaurant *inn, t_philosoph *philo,  char *message)
{
	int		i;

	i = -1;
	if (inn)
	{
		while (++i < inn->guest_nb)
		{
			sem_post(inn->one_full);
			sem_post(inn->one_dead);
			sem_post(inn->forks);
			sem_post(inn->speak);
			sem_post(inn->quit);
		}
		close_establishment(inn);
	}
	if (!message)
		printf("%s", USAGE);
	else
		printf("%s", message);
	if (philo)
	{
		close_customer_sem(philo);
		sem_unlink(philo->starv_n);
		sem_unlink(philo->stom_n);
		exit(-1);
	}
	return (-1);
}

int	communication(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc < 5 || argc > 6)
		return (-1);
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if ((argv[i][j] > '9' || argv[i][j] < '0') && argv[i][j] != '-')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_restaurant	inn;

	if (communication(argc, argv) == -1)
		return (emergency_exit(NULL, NULL, NULL));
	else if (open_restaurant(&inn, argc, argv) == -1)
		return (emergency_exit(NULL, NULL, "fail opening restaurant\n"));
	else if (welcome_customers(&inn) == -1)
		return (emergency_exit(&inn, NULL, "Customers has been kicked out\n"));
	else if (get_staff_ready(&inn) == -1)
		return (emergency_exit(&inn, NULL, "Staff is leaving\n"));
	wait_everybody(&inn);
	close_establishment(&inn);
	unlink_sem();
	return (0);
}
