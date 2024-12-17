/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:22:39 by npolack           #+#    #+#             */
/*   Updated: 2024/12/13 12:11:26 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

typedef struct s_philosoph
{
	pthread		itself;
	int			id;
	int			eating;
	int			sleeping;
	int			thinking;
	int			dead;
	int			fork;
	
} t_philosoph;

typedef struct	s_restaurant
{
	int			time_to_sleep;
	int			time_to_eat;
	int			time_to_die;
	int			guest_nb;
	int			*forks[];
	t_philosoph	*philo;
	pthread		table,
	int			all_dead;
}


