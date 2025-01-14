/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_sem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:24:01 by npolack           #+#    #+#             */
/*   Updated: 2025/01/14 12:59:15 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		i;
	char	sem_name[3];

	if (sem_unlink("/silverware") == -1)
		perror("silverware");
	if (sem_unlink("/speaker") == -1)
		perror("speaker");
	if (sem_unlink("/death") == -1)
		perror("death");
	if (sem_unlink("/full") == -1)
		perror("full");
	i = 0;
	while (i < atoi(argv[1]))
	{
		sem_name[0] = '/';
		sem_name[1] = 'A' + i;
		sem_name[2] = '\0';
		if (sem_unlink(sem_name) == -1)
			perror (sem_name);
		i++;
	}
}
