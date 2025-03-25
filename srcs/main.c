/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natgomali <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:04:39 by natgomali         #+#    #+#             */
/*   Updated: 2025/03/24 17:21:04 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	meal_philo_done(t_philo *philo, t_infos *infos)
{
	int	meal;

	meal = 0;
	pthread_mutex_lock(&infos->eat);
	meal += philo->nb_meal;
	pthread_mutex_unlock(&infos->eat);
	if (meal >= infos->max_eat)
		return (1);
	return (0);
}

int check_philo(t_philo *philo, t_infos *infos)
{
	long	actual_time;
	int		full_meal;
	int		i;

	i = 0;
	actual_time = ft_time();
	pthread_mutex_lock(&infos->eat_check);
	while (i < infos->nb_philo)
	{
		full_meal += meal_philo_done(&philo[i], infos);
		if (actual_time - philo[i].last_meal > infos->ttdie)
		{
			print_time("died", actual_time, &philo[i], infos);
			return (1);
		}
		i++;
	}
	if (full_meal == infos->max_eat && check_state(infos) == 0)
		return (-1);
	pthread_mutex_unlock(&infos->eat_check);
	return (0);
}

static void	return_is_end(t_infos *infos, t_philo *philo)
{		
	int	i;
	int	meal_done;

	while (check_state(infos) == 0)
	{
		i = 0;
			while (i < infos->nb_philo)
			{
				meal_done = 0;
				meal_done = check_philo(&philo[i], infos);
				if (meal_done == -1)
				{
					pthread_mutex_lock(&infos->state_check);
					infos->state = -1;
					pthread_mutex_lock(&infos->state_check);
				}
				else if (meal_done == infos->max_eat && check_state(infos) == 1)
				{
					pthread_mutex_lock(&infos->state_check);
					infos->state = 1;
					pthread_mutex_lock(&infos->state_check);
				}
				usleep(50);
				i++;
			}
	}
	return ;
}

int main(int argc, char **argv)
{
	t_infos	*infos;
	t_philo	*philo;
	int		i;

	i = 0;
	if (argc < 5 || argc > 6)
		ft_putstr_exit("Error : Exactly 4 or 5 args required\n", 2);
	infos = ft_parsing(argc, argv);
	philo = init_philo(infos);
	pthread_mutex_lock(&infos->init);
	while (i < infos->nb_philo)
	{
		if (pthread_create(&philo[i].id, NULL, &ft_routine, &philo[i]))
			return (1);
		i++;
	}
	set_time_all(philo, infos);
	pthread_mutex_unlock(&infos->init);
	return_is_end(infos, philo);
	ft_clean_exit(philo, infos);
	return (1);
}
