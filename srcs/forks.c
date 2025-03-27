/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:17:45 by namalier          #+#    #+#             */
/*   Updated: 2025/03/27 13:18:18 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	odd_forks(t_philo *philo, t_infos *infos)
{
	pthread_mutex_lock(&philo->fork_r);
	print_time("has taken a fork", ft_time() - philo->start, philo, infos);
	if (infos->nb_philo != 1)
	{
		pthread_mutex_lock(philo->fork_l);
		print_time("has taken a fork", ft_time() - philo->start, philo, infos);
	}
	else
	{
		pthread_mutex_lock(&infos->state_check);
		infos->state = 1;
		pthread_mutex_unlock(&infos->state_check);
		usleep(infos->ttdie * 1000);
		print_die(ft_time() - philo->start, philo, infos);
	}
}

void	take_forks(t_philo *philo, t_infos *infos)
{
	if (philo->name % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_l);
		print_time("has taken a fork", ft_time() - philo->start, philo, infos);
		pthread_mutex_lock(&philo->fork_r);
		print_time("has taken a fork", ft_time() - philo->start, philo, infos);
	}
	else
		odd_forks(philo, infos);
}

void	ft_forks_down(t_philo *philo)
{
	if (philo->name % 2 != 0 && philo->infos->nb_philo != 1)
	{
		pthread_mutex_unlock(&philo->fork_r);
		pthread_mutex_unlock(philo->fork_l);
	}
	else if (philo->name % 2 == 0 && philo->infos->nb_philo != 1)
	{
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(&philo->fork_r);
	}
	else if (philo->infos->nb_philo == 1)
		pthread_mutex_unlock(&philo->fork_r);
}
