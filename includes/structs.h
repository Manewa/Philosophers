/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natgomali <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:55:44 by natgomali         #+#    #+#             */
/*   Updated: 2025/03/27 13:50:11 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_infos
{
	int				nb_philo;
	int				state;
	long			ttdie;
	long			ttthink;
	long			tteat;
	long			ttsleep;
	long			start_time;
	int				max_eat;
	pthread_mutex_t	write;
	pthread_mutex_t	eat;
	pthread_mutex_t	eat_check;
	pthread_mutex_t	init;
	pthread_mutex_t	state_check;
	pthread_mutex_t	time;
}				t_infos;

typedef struct s_philo
{
	int				name;
	int				state;
	int				meal_state;
	pthread_t		id;
	long			start;
	long			last_meal;
	pthread_mutex_t	fork_r;
	pthread_mutex_t	*fork_l;
	int				nb_meal;
	t_infos			*infos;
}				t_philo;

#endif
