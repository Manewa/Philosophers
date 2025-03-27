/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:38:50 by namalier          #+#    #+#             */
/*   Updated: 2025/03/27 13:42:14 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_mutex_infos(t_infos *infos)
{
	pthread_mutex_init(&infos->write, NULL);
	pthread_mutex_init(&infos->eat, NULL);
	pthread_mutex_init(&infos->eat_check, NULL);
	pthread_mutex_init(&infos->init, NULL);
	pthread_mutex_init(&infos->state_check, NULL);
	pthread_mutex_init(&infos->time, NULL);
}
