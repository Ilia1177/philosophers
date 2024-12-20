/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:29:55 by npolack           #+#    #+#             */
/*   Updated: 2024/12/20 17:16:02 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	look_at_the_time(struct timeval *start)
{
	struct timeval	current_time;
	long long		sec;
	long long		usec;

	gettimeofday(&current_time, NULL);
	sec = current_time.tv_sec - start->tv_sec;
	usec = current_time.tv_usec - start->tv_usec;
	return ((sec * 1000LL) + (usec / 1000));
}

void	announce(char *message, t_philosoph *philo)
{
	struct timeval	*start;

	start = philo->start;
	pthread_mutex_lock(philo->order);
	printf("\033[33m %lld \033[32m %d %s\n\033[0m", look_at_the_time(start), philo->id, message);
	pthread_mutex_unlock(philo->order);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;

	sign = 1;
	result = 0;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
	{
		sign *= -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr) - '0';
		nptr++;
	}
	return (result * sign);
}

int	str_overflow(const char *nptr)
{
	int	result;
	int	sign;

	sign = 1;
	result = 0;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
	{
		sign *= -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr) - '0';
		nptr++;
	}
	return (result * sign);
}
