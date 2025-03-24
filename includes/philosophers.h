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

int	main(int argc, char **arv);

/*** parsing.c ***/

t_infos	*ft_parsing(int argc, char **argv);

/*** utils.c ***/

void	ft_putstr_exit(char *s, int fd);
t_infos	*ft_infonew(char **argv, int argc);

#endif
