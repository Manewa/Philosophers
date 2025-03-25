#include "../includes/philosophers.h"

static void odd_forks(t_philo *philo, t_infos *infos)
{
	pthread_mutex_lock(&philo->fork_r);
	print_time("has taken a fork", ft_time() - philo->start, philo, infos);
	if (infos->nb_philo == 1)
	{
		usleep(infos->ttdie * 1000);
		check_philo(philo, infos);
	}
	else
	{
		pthread_mutex_lock(philo->fork_l);
		print_time("has taken a fork", ft_time() - philo->start, philo, infos);
	}
}

void take_forks(t_philo *philo, t_infos *infos)
{
	if (philo->name % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_l);
		print_time("has taken a fork", ft_time() - philo->start, philo, infos);
		pthread_mutex_lock(&philo->fork_r);
		print_time("has taken a fork", ft_time() - philo->start, philo, infos);
	}
	else
        odd_forks(philo, infos);
}

void	ft_forks_down(t_philo *philo)
{
	if (philo->infos->nb_philo == 1)
		pthread_mutex_unlock(&philo->fork_r);
	else if (philo->name % 2 != 0)
	{
		pthread_mutex_unlock(&philo->fork_r);
		pthread_mutex_unlock(philo->fork_l);
	}
	else
	{
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(&philo->fork_r);
	}
}
