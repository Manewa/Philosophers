/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natgomali <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:49:21 by natgomali         #+#    #+#             */
/*   Updated: 2025/03/25 20:42:23 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void ft_eat(t_infos *infos, t_philo *philo)
{
	take_forks(philo, infos);
	pthread_mutex_lock(&infos->eat);
	philo->last_meal = ft_time();
	philo->nb_meal += 1;
	pthread_mutex_unlock(&infos->eat);
	print_time("is eating", ft_time() - philo->start, philo, infos);
	ft_usleep(ft_time(), infos->tteat, infos);
	ft_forks_down(philo);
}

void ft_sleep(t_infos *infos, t_philo *philo)
{
	print_time("is sleeping", ft_time() - philo->start, philo, infos);
	ft_usleep(ft_time(), infos->ttsleep, infos);
}

void ft_think(t_infos *infos, t_philo *philo)
{
	print_time("is thinking", ft_time() - philo->start, philo, infos);
//	if (infos->nb_philo % 2)
//		ft_usleep(ft_time(), infos->ttthink, infos);
//	else
		usleep(100);
}

void	*ft_routine(void *args)
{
	t_philo	*philo;
	t_infos	*infos;

	philo = (t_philo *)args;
	infos = philo->infos;
	pthread_mutex_lock(&infos->init);
	philo->start = infos->start_time;
	pthread_mutex_unlock(&infos->init);
	if (philo->name % 2 == 0)
		ft_usleep(philo->start, infos->tteat / 2, infos);
	else if (infos->nb_philo % 2 != 0 && philo->name == 1
			&& infos->nb_philo != 1)
		ft_usleep(philo->start, infos->tteat, infos);
	while (check_state(infos) == 0)
	{
		ft_eat(infos, philo);
		ft_sleep(infos,philo);
		ft_think(infos, philo);
	}
	return (NULL);
}
