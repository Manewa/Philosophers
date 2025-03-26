/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natgomali <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:55:49 by natgomali         #+#    #+#             */
/*   Updated: 2025/03/20 16:35:26 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libs.h"
# include "structs.h"


/*** main.c ***/

int check_philo(t_philo *philo, t_infos *infos);
int	main(int argc, char **arv);

/*** parsing.c ***/

void check_args(t_infos *infos, int argc);
t_infos	*ft_parsing(int argc, char **argv);

/*** utils.c ***/

int	ft_atoi(const char *str);
void	ft_putstr_exit(char *s, int fd);
void print_time(char *str, long time, t_philo *philo, t_infos *infos);
void print_die(long time, t_philo *philo, t_infos *infos);

/*** utils_philo.c ***/

t_infos	*ft_infonew(char **argv, int argc);
long ft_time(void);
void	set_time_all(t_philo *philo, t_infos *infos);
int	check_state(t_infos *infos);
void ft_usleep(long start, long wait, t_infos *infos);

/*** init_philo.c ***/

t_philo *init_philo(t_infos *infos);

/*** routine.c ***/

void	*ft_routine(void *args);

/*** forks.c ***/

void take_forks(t_philo *philo, t_infos *infos);
void ft_forks_down(t_philo *philo);

/*** clean_exit.c ***/

void ft_clean_exit(t_philo *philo, t_infos *infos);

#endif
