#include "../includes/philosophers.h"

t_infos	*ft_infonew(char **argv, int argc)
{
	t_infos	*infos;

	infos = malloc(sizeof(t_infos));
	if(!infos)
		exit(2);
	infos->nb_philo = ft_atoi(argv[1]);
	infos->ttdie = ft_atoi(argv[2]);
	infos->tteat = ft_atoi(argv[3]);
	infos->ttsleep = ft_atoi(argv[4]);
	infos->max_eat = 0;
	infos->start_time = ft_time();
	if (argc == 6)
		infos->max_eat = ft_atoi(argv[5]);
	infos->state = 0;
	if (2 * infos->tteat >= infos->ttsleep)
		infos->ttthink = infos->tteat * 2 - infos->ttsleep;
	else
		infos->ttthink = infos->ttsleep - 2 * infos->tteat;
	check_args(infos, argc);
	pthread_mutex_init(&infos->write, NULL);
	pthread_mutex_init(&infos->eat, NULL);
	pthread_mutex_init(&infos->eat_check, NULL);
	pthread_mutex_init(&infos->init, NULL);
	pthread_mutex_init(&infos->state_check, NULL);
	pthread_mutex_init(&infos->time, NULL);
	return(infos);
}

long ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	set_time_all(t_philo *philo, t_infos *infos)
{
	int	i;

	i = 0;
	infos->start_time = ft_time();
	while (i < infos->nb_philo)
	{
		philo[i].last_meal = infos->start_time;
		i++;
	}
}

int	check_state(t_infos *infos)
{
	int	state;

	pthread_mutex_lock(&(infos->state_check));
	state = infos->state;
	pthread_mutex_unlock(&(infos->state_check));
	return (state);
}

void ft_usleep(long start, long wait, t_infos *infos)
{
	long	current;
	long	time_left;

	while (check_state(infos) == 0)
	{
		current = ft_time();
		time_left = wait - (current - start);
		if (time_left <= 0)
			break ;
		else if (time_left > 10)
			usleep(1000);
		else
			usleep(time_left * 1000);
	}
}
