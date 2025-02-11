/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilia <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:51:45 by ilia              #+#    #+#             */
/*   Updated: 2025/01/26 18:52:46 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	take_time(t_philosoph *philo, int time)
{
	long long	start;
	long long	current;

	start = look_at_the_time(&philo->start) / 1000;
	current = start;
	while (current < start + time && !is_starving(philo))
	{
		usleep(50);
		current = look_at_the_time(&philo->start) / 1000;
	}
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

int	ft_strcmp(const char *s1, const char *s2)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		result += ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (result != 0)
			return (result);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	speak_poetry(char *poem, t_philosoph *philo)
{
	long long		instant;
	int				color;

	color = philo->id + 30;
	sem_wait(philo->speak);
	if (is_starving(philo))
	{
		sem_post(philo->speak);
		return ;
	}
	instant = look_at_the_time(&philo->start) / 1000;
	printf("\033[%dm%04lld %3d %s\033[0m\n", color, instant, philo->id, poem);
	if (!ft_strcmp(poem, "died"))
		sem_post(philo->quit);
	else
		sem_post(philo->speak);
}

// return time spend from start in usec (usec * 1000 = ms)
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
