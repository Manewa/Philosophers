/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natgomali <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:23:55 by natgomali         #+#    #+#             */
/*   Updated: 2025/03/25 18:26:21 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void check_args(t_infos *infos, int argc)
{
	if (infos->nb_philo < 0)
	{
		free(infos);
		ft_putstr_exit("Error: At least one philosopher is needed\n", 2);
	}
	else if (infos->ttdie < 1 || infos->tteat < 1 || infos->ttsleep < 1)
	{
		free(infos);
		ft_putstr_exit("Error: No time can be below 1\n", 2);
	}
	else if (infos->nb_philo > 200)
	{
		free(infos);
		ft_putstr_exit("Error: Too much philosophers (+200)\n", 2);
	}
	else if (argc == 6 && infos->max_eat < 1)
	{
		free(infos);
		ft_putstr_exit("Error: Philosophers need at least one meal\n", 2);
	}
}

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
	t_infos	*infos;

	check_numbers(argv);
	infos = ft_infonew(argv, argc);
	return (infos);
}
