/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natgomali <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:46:59 by natgomali         #+#    #+#             */
/*   Updated: 2025/03/27 13:18:58 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_clean_philo(t_philo *philo, t_infos *infos)
{
	int	i;

	i = 0;
	usleep(1000);
	while (i < infos->nb_philo)
	{
		if (pthread_join(philo[i].id, NULL) != 0)
			write(2, "Error join\n", 11);
		i++;
	}
	while (--i >= 0)
		pthread_mutex_destroy(&philo[i].fork_r);
	free(philo);
}

void	ft_clean_exit(t_philo *philo, t_infos *infos)
{
	ft_clean_philo(philo, infos);
	pthread_mutex_destroy(&infos->write);
	pthread_mutex_destroy(&infos->eat);
	pthread_mutex_destroy(&infos->init);
	pthread_mutex_destroy(&infos->time);
	pthread_mutex_destroy(&infos->state_check);
	free(infos);
}
