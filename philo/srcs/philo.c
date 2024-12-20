/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:15:52 by npolack           #+#    #+#             */
/*   Updated: 2024/12/20 16:40:19 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	emergency_exit(char *message)
{
	printf("%s", message);
	return (0);
}

int	main(int argc, char **argv)
{
	t_restaurant	inn;
	char			*usage;
	int				i;

	usage = "usage : <philo_nb> <t_die> <t_eat> <t_sleep> [max_meal]\n";
	if (argc < 5 || argc > 6)
		return (emergency_exit(usage));
	open_restaurant(&inn, argc, argv);
	supervise(&inn);
	dress_a_table(&inn);
	i = 0;
	while (i < inn.guest_nb)
	{
		pthread_join(inn.philo[i].itself, NULL);
		i++;
	}
	pthread_join(inn.table, NULL);
	pthread_mutex_unlock(&inn.order);
	close_establishment(&inn);
	return (0);
}
