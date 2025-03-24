/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natgomali <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:23:55 by natgomali         #+#    #+#             */
/*   Updated: 2025/03/20 16:48:41 by natgomali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void check_numbers(char **argv)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				ft_putstr_exit("Error: Only numbers tolerate in args\n", 2);
			j++;
		}
		i++;
	}
}

t_infos	*ft_parsing(int argc, char **argv)
{
	size_t	i;
	t_infos	*infos;

	(void)i;
	check_numbers(argv);
	infos = ft_infonew(argv, argc);
	return (infos);
}
