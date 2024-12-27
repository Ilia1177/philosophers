	/* ************************************************************************** */
	/*                                                                            */
	/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
	/*                                                    +:+ +:+         +:+     */
	/*   By: ilia <marvin@42.fr>                        +#+  +:+       +#+        */
	/*                                                +#+#+#+#+#+   +#+           */
	/*   Created: 2024/12/21 18:05:14 by ilia              #+#    #+#             */
/*   Updated: 2024/12/26 20:11:35 by ilia             ###   ########.fr       */
	/*                                                                            */
	/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	emergency_exit(t_restaurant *inn, char *message)
{
	char *usage;
	(void)inn;

	usage = "usage : <philo_nb> <t_die> <t_eat> <t_sleep> [max_meal]\n";
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
			if ((argv[i][j] > '9' || argv[i][j] < '0') && argv[i][j] != '-')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}



int main(int argc, char **argv)
{
	t_restaurant	inn;
	
	if (argc < 5 || argc > 6 || communication(argc, argv) == -1)
		return (emergency_exit(&inn, NULL));
	open_restaurant(&inn, argc, argv);
	welcome_customers(&inn);
	while (waitpid(-1, NULL, 0))
		;
	close_establishment(&inn);
	return (0);	
}
