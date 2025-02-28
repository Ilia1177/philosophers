/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:15:52 by npolack           #+#    #+#             */
/*   Updated: 2025/02/28 13:51:35 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	emergency_exit(t_restaurant *inn, char *message)
{
	char	*usage;

	usage = "usage : <philo_nb> <t_die> <t_eat> <t_sleep> [max_meal]\n";
	if (inn)
	{
		free(inn->philo);
		pthread_mutex_destroy(&inn->order);
	}
	if (!message)
		printf("%s", usage);
	else
		printf("%s", message);
	return (0);
}

int	communication(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if ((argv[i][j] > '9' || argv[i][j] < '0'))
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
	int				i;

	inn.philo = NULL;
	if (argc < 5 || argc > 6 || communication(argc, argv) == -1)
		return (emergency_exit(NULL, NULL));
	if (open_restaurant(&inn, argc, argv) == -1)
		return (emergency_exit(&inn, "only accept strict positive int\n"));
	if (dress_a_table(&inn) == -1)
		return (emergency_exit(&inn, "fail making philo\n"));
	i = -1;
	while (++i < inn.guest_nb)
		pthread_join(inn.philo[i].itself, NULL);
	pthread_mutex_destroy(&inn.order);
	close_establishment(&inn, 0, 0);
	free(inn.philo);
	return (0);
}
