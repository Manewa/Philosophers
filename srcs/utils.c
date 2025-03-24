/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natgomali <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:04:03 by natgomali         #+#    #+#             */
/*   Updated: 2025/03/24 12:52:13 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	ft_atoi(const char *str)
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

static void check_args(t_infos *infos, int argc)
{
	if (infos->nb_philo < 0)
	{
		free(infos);
		ft_putstr_exit("Error: At least one philosopher is needed\n", 2);
	}
	else if (infos->ttdie < 1 || infos->tteat < 1 || infos->ttsleep < 1)
	{
		free(infos);
		ft_putstr_exit("Error: No time can be below 1\n", 2);
	}
	else if (infos->nb_philo > 200)
	{
		free(infos);
		ft_putstr_exit("Error: Too much philosophers (200)\n", 2);
	}
	else if (argc == 6 && infos->max_eat < 1)
	{
		free(infos);
		ft_putstr_exit("Error: Philosophers need at least one meal\n", 2);
	}
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

t_infos	*ft_infonew(char **argv, int argc)
{
	t_infos	*infos;

	infos = malloc(sizeof(t_infos));
	if(!infos)
		exit(2);
	infos->nb_philo = ft_atoi(argv[1]);
	infos->ttdie = ft_atoi(argv[2]);
	infos->tteat = ft_atoi(argv[3]);
	infos->ttsleep = ft_atoi(argv[4]);
	infos->max_eat = 0;
	infos->start_time = ft_time();
	if (argc == 6)
		infos->max_eat = ft_atoi(argv[5]);
	infos->state = 0;
	if (2 * infos->tteat > infos ->ttsleep)
		infos->ttthink = infos->tteat * 2 - infos->ttsleep;
	else
		infos->ttthink = infos->ttsleep - 2 * infos->tteat;
	check_args(infos, argc);
	pthread_mutex_init(&infos->write, NULL);
	pthread_mutex_init(&infos->eat, NULL);
	pthread_mutex_init(&infos->init, NULL);
	pthread_mutex_init(&infos->state_check, NULL);
	pthread_mutex_init(&infos->time, NULL);
	return(infos);
}

long ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	set_time_all(t_philo *philo, t_infos *infos)
{
	int	i;

	i = 0;
	infos->start_time = ft_time();
	while (i < infos->nb_philo)
	{
		philo[i].last_meal = infos->start_time;
		i++;
	}
}

int	check_state(t_infos *infos)
{
	int	state;

	pthread_mutex_lock(&(infos->state));
	state = infos->state;
	pthread_mutex_unlock(&(infos->state));
	return (state);
}

void print_time(char *str, long time, t_philo *philo, t_infos *infos)
{
	pthread_mutex_lock(&infos->state_check);
	pthread_mutex_lock(&infos->write);
	printf("%ld %d %s\n", time, philo->name, str);
	pthread_mutex_unlock(&infos->state_check);
	pthread_mutex_unlock(&infos->write);
}

void ft_usleep(long start, long wait, t_infos *infos)
{
	long	current;
	long	time_left;

	while (get_state(infos) == 0)
	{
		current = ft_time();
		time_left = wait - (current - start);
		if (time_left <= 0)
			break ;
		else if (time_left > 10)
			usleep(1000);
		else
			usleep(time_left * 1000);
	}
}
