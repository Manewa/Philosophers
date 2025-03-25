/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natgomali <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:49:21 by natgomali         #+#    #+#             */
/*   Updated: 2025/03/24 17:02:17 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void ft_eat(t_infos *infos, t_philo *philo)
{
	long	time;

	time = ft_time();
	take_forks(philo, infos);
	pthread_mutex_lock(&infos->eat);
	philo->last_meal = time;
	philo->nb_meal += 1;
	print_time("is eating", time - philo->start, philo, infos);
	ft_usleep(time, infos->tteat, infos);
	ft_forks_down(philo);
	pthread_mutex_unlock(&infos->eat);
}

void ft_sleep(t_infos *infos, t_philo *philo)
{
	long	time;

	time = ft_time();
	print_time("is sleeping", time - philo->start, philo, infos);
	ft_usleep(time, infos->ttsleep, infos);
}

void ft_think(t_infos *infos, t_philo *philo)
{
	long	time;

	time = ft_time();
	print_time("is thinking", time - philo->start, philo, infos);
	if (infos->nb_philo % 2 == 0)
		ft_usleep(time, infos->ttthink, infos);
	else
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
		ft_think(infos, philo);
		ft_eat(infos, philo);
		ft_sleep(infos,philo);
	}
	return (NULL);
}
