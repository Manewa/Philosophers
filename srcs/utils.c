/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natgomali <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:04:03 by natgomali         #+#    #+#             */
/*   Updated: 2025/03/27 13:14:37 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	while (str && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str && str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - 48;
		i++;
	}
	return (num * sign);
}

static size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_exit(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (i < ft_strlen(s))
	{
		write(fd, &s[i], 1);
		i++;
	}
	exit(2);
}

void	print_time(char *str, long time, t_philo *philo, t_infos *infos)
{
	pthread_mutex_lock(&infos->state_check);
	pthread_mutex_lock(&infos->write);
	if (infos->state == 0)
		printf("%ld %d %s\n", time, philo->name, str);
	pthread_mutex_unlock(&infos->state_check);
	pthread_mutex_unlock(&infos->write);
}

void	print_die(long time, t_philo *philo, t_infos *infos)
{
	pthread_mutex_lock(&infos->write);
	printf("%ld %d died\n", time, philo->name);
	pthread_mutex_unlock(&infos->write);
}
