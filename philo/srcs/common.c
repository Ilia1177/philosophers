/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:29:55 by npolack           #+#    #+#             */
/*   Updated: 2025/01/26 14:54:05 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	digest_meal(t_philosoph *philo)
{
	pthread_mutex_lock(&philo->stomach);
	if (philo->max_meal > 0)
		philo->max_meal--;
	pthread_mutex_unlock(&philo->stomach);
}

void	take_time(t_philosoph *philo, int time)
{
	long long	start;
	long long	current;

	start = look_at_the_time(philo->start) / 1000;
	current = start;
	while (current < start + time && !is_starving(philo))
	{
		usleep(1000);
		current = look_at_the_time(philo->start) / 1000;
	}
}

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
	int				color;

	color = philo->id + 30;
	start = philo->start;
	pthread_mutex_lock(philo->order);
	if (is_starving(philo))
	{
		pthread_mutex_unlock(philo->order);
		return ;
	}
	instant = look_at_the_time(start) / 1000;
	printf("\033[%dm%04lld %3d %s\033[0m\n", color, instant, philo->id, poem);
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
