/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilia <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 18:05:14 by ilia              #+#    #+#             */
/*   Updated: 2025/01/26 18:18:57 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	emergency_exit(t_restaurant *inn, char *message)
{
	char	*usage;
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
	usage = "usage : <philo_nb> <t_die> <t_eat> <t_sleep> [max_meal]\n";
	if (!message)
		printf("%s", usage);
	else
		printf("%s", message);
	exit(-1);
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
		return (emergency_exit(NULL, NULL));
	if (open_restaurant(&inn, argc, argv) == -1)
		return (emergency_exit(NULL, "fail opening restaurant\n"));
	if (welcome_customers(&inn) == -1)
		return (emergency_exit(&inn, "Customers has been kicked out\n"));
	if (get_staff_ready(&inn) == -1)
		return (emergency_exit(&inn, "Staff is leaving\n"));
	wait_everybody(&inn);
	if (close_establishment(&inn) == -1)
		return (emergency_exit(&inn, "fail in exit\n"));
	return (0);
}
