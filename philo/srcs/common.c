/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:29:55 by npolack           #+#    #+#             */
/*   Updated: 2024/12/21 04:09:24 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <limits.h>

long long	look_at_the_time(struct timeval *start)
{
	struct timeval	current_time;
	long long		sec;
	long long		usec;

	gettimeofday(&current_time, NULL);
	sec = current_time.tv_sec - start->tv_sec;
	usec = current_time.tv_usec - start->tv_usec;
	return ((sec * 1000000LL) + (usec));
}

void	speak_poetry(char *poem, t_philosoph *philo)
{
	struct timeval	*start;
	long long		instant;

	if (philo->dead)
		return ;
	start = philo->start;
	pthread_mutex_lock(philo->order);
	if (philo->dead)
	{
		pthread_mutex_unlock(philo->order);
		return ;
	}
	instant = look_at_the_time(start) / 1000;
	if (philo->id % 5 == 0)
		printf("\033[31m %04lld %3d %s\033[0m\n", instant, philo->id, poem);
	else if (philo->id % 5 == 1)                 
		printf("\033[32m %04lld %3d %s\033[0m\n", instant, philo->id, poem);
	else if (philo->id % 5 == 2)                 
		printf("\033[33m %04lld %3d %s\033[0m\n", instant, philo->id, poem);
	else if (philo->id % 5 == 3)                 
		printf("\033[34m %04lld %3d %s\033[0m\n", instant, philo->id, poem);
	else if (philo->id % 5 == 4)                 
		printf("\033[35m %04lld %3d %s\033[0m\n", instant, philo->id, poem);
	pthread_mutex_unlock(philo->order);
}


void	announce(char *message, t_philosoph *philo)
{
	struct timeval	*start;
	long long	instant;

	start = philo->start;
	pthread_mutex_lock(philo->order);
	instant = look_at_the_time(start) / 1000;
	printf("\033[33m %lld \033[32m %d %s\n\033[0m", instant, philo->id, message);
	pthread_mutex_unlock(philo->order);
}

int	ft_atoi(const char *nptr, int *result)
{
	int	sign;
	int	digit;

	*result = 0;
	sign = 1;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
		return (-1);
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		digit = *nptr - '0';
        if (sign == 1 && (*result > (INT_MAX - digit) / 10))
            return (-1);
        if (sign == -1 && (*result < (INT_MIN + digit) / 10))
            return (-1);
		*result = *result * 10 + sign * digit;
		nptr++;
	}
	return (0);
}
