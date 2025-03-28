/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natgomali <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:34:48 by natgomali         #+#    #+#             */
/*   Updated: 2025/03/27 13:18:41 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	ft_init_forks(t_philo *philo, int i)
{
	pthread_mutex_init(&philo[i].fork_r, NULL);
	if (i > 0)
		philo[i].fork_l = &philo[i - 1].fork_r;
}

t_philo	*init_philo(t_infos *infos)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(infos->nb_philo * sizeof(t_philo));
	if (!philo)
		return (free(infos), NULL);
	philo[0].fork_l = NULL;
	while (i < infos->nb_philo)
	{
		philo[i].name = i + 1;
		philo[i].state = 0;
		philo[i].nb_meal = 0;
		philo[i].infos = infos;
		ft_init_forks(philo, i);
		i++;
	}
	if (infos->nb_philo > 1)
		philo[0].fork_l = &philo[infos->nb_philo - 1].fork_r;
	return (philo);
}
