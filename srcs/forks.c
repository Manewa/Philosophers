#include "../includes/philosophers.h"

static void odd_forks(long time, t_philo *philo, t_infos *infos)
{
	pthread_mutex_lock(&philo->fork_r);
	print_time("has taken a fork", time, philo, infos);
	if (infos->nb_philo == 1)
	{
		usleep(infos->ttdie * 1000);
		check_philo(philo, infos);
	}
	else
	{
		pthread_mutex_lock(philo->fork_l);
		print_time("has taken a fork", time, philo, infos);
	}
}

void take_forks(t_philo *philo, t_infos *infos)
{
	long	time;

	time = ft_time();
	if (philo->name % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_l);
		print_time("has taken a fork", time - philo->start, philo, infos);
		pthread_mutex_lock(&philo->fork_r);
		print_time("has taken a fork", time - philo->start, philo, infos);
	}
	else
        odd_forks(time, philo, infos);
}

void	ft_forks_down(t_philo *philo)
{
	if (philo->fork_l == NULL)
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
