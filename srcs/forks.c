/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:17:45 by namalier          #+#    #+#             */
/*   Updated: 2025/03/28 14:40:53 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	take_forks(t_philo *philo, t_infos *infos)
{
	if (philo->name % 2 != 0)
	{
		pthread_mutex_lock(&philo->fork_r);
		print_time("has taken a fork", ft_time() - philo->start, philo, infos);
		if (infos->nb_philo != 1)
		{
			pthread_mutex_lock(philo->fork_l);
			print_time("has taken a fork", ft_time() - philo->start,
				philo, infos);
		}
		else
			usleep(infos->ttdie * 1000);
	}	
	else
	{
		pthread_mutex_lock(philo->fork_l);
		print_time("has taken a fork", ft_time() - philo->start, philo, infos);
		pthread_mutex_lock(&philo->fork_r);
		print_time("has taken a fork", ft_time() - philo->start, philo, infos);
	}
}

void	ft_forks_down(t_philo *philo)
{
	if (philo->name % 2 != 0 && philo->infos->nb_philo != 1)
	{
		pthread_mutex_unlock(&philo->fork_r);
		pthread_mutex_unlock(philo->fork_l);
	}
	else if (philo->infos->nb_philo != 1)
	{
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(&philo->fork_r);
	}
	else
		pthread_mutex_unlock(&philo->fork_r);
}
