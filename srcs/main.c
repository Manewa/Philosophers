/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natgomali <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:04:39 by natgomali         #+#    #+#             */
/*   Updated: 2025/03/28 12:52:16 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	meal_philo_done(t_philo *philo, t_infos *infos)
{
	int	meal;

	pthread_mutex_lock(&infos->eat_check);
	meal = philo->state;
	pthread_mutex_unlock(&infos->eat_check);
	if (infos->max_eat != 0 && meal == 1)
		return (1);
	return (0);
}

int	check_philo(t_philo *philo, t_infos *infos)
{
	int		full_meal;
	int		i;

	i = 0;
	full_meal = 0;
	while (i < infos->nb_philo)
	{
		pthread_mutex_lock(&infos->eat);
		if (ft_time() - philo[i].last_meal >= infos->ttdie)
		{
			print_die(ft_time() - infos->start_time, &philo[i], infos);
			return (1);
		}
		pthread_mutex_unlock(&infos->eat);
		if (infos->max_eat > 0)
			full_meal += meal_philo_done(&philo[i], infos);
		i++;
		usleep(100);
	}
	if (infos->max_eat > 0 && full_meal == infos->nb_philo)
		return (-1);
	return (0);
}

static void	return_is_end(t_infos *infos, t_philo *philo)
{		
	int	meal_done;

	pthread_mutex_unlock(&infos->init);
	while (1)
	{
		meal_done = 0;
		meal_done = check_philo(philo, infos);
		if (meal_done == -1)
		{
			pthread_mutex_lock(&infos->state_check);
			infos->state = -1;
			pthread_mutex_unlock(&infos->state_check);
			break ;
		}
		else if (meal_done == 1)
		{
			pthread_mutex_lock(&infos->state_check);
			infos->state = 1;
			pthread_mutex_unlock(&infos->state_check);
			pthread_mutex_unlock(&infos->eat);
			break ;
		}
		usleep(100);
	}
	return ;
}

int	main(int argc, char **argv)
{
	t_infos	*infos;
	t_philo	*philo;
	int		i;

	i = 0;
	if (argc < 5 || argc > 6)
		ft_putstr_exit("Error : Exactly 4 or 5 args required\n", 2);
	infos = ft_parsing(argc, argv);
	philo = init_philo(infos);
	if (!philo)
		return (1);
	pthread_mutex_lock(&infos->init);
	while (i < infos->nb_philo)
	{
		if (pthread_create(&philo[i].id, NULL, &ft_routine, &philo[i]))
			return (write(2, "Error when thread created", 25));
		i++;
	}
	set_time_all(philo, infos);
	return_is_end(infos, philo);
	ft_clean_exit(philo, infos);
	return (1);
}
