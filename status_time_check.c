/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_time_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:59:00 by melkholy          #+#    #+#             */
/*   Updated: 2023/02/16 20:30:24 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_must_eat(t_philo *philo)
{
	if (philo->number_must_eat < 0)
		return ;
	philo->eat_count ++;
	if (philo->eat_count == philo->number_must_eat)
	{
		pthread_mutex_lock(&philo->st_death->st_lock);
		philo->status[1]++;
		pthread_mutex_unlock(&philo->st_death->st_lock);
	}
}

int	ft_check_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->st_death->st_lock);
	if (philo->status[0] == 1 || philo->status[1] == philo->num_philo)
	{
		pthread_mutex_unlock(&philo->st_death->st_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->st_death->st_lock);
	return (0);
}

void	ft_pa_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->st_death->st_lock);
	philo->status[0] = 1;
	pthread_mutex_unlock(&philo->st_death->st_lock);
}

void	ft_mysleep(t_philo *philo, long millisecond)
{
	long	predict_time;
	long	death_time;
	int		flag;

	death_time = philo->start_time + philo->time_to_die;
	predict_time = ft_current_time() + millisecond;
	flag = 0;
	while (ft_current_time() < predict_time)
	{
		if (ft_current_time() >= death_time && !flag)
		{
			pthread_mutex_lock(&philo->st_death->pt_lock);
			if (ft_check_status(philo))
			{
				pthread_mutex_unlock(&philo->st_death->pt_lock);
				break ;
			}
			ft_pa_death(philo);
			printf("%ld %d died\n", death_time, philo->id);
			pthread_mutex_unlock(&philo->st_death->pt_lock);
			flag = 1;
		}
		usleep(100);
	}
}

int	ft_check_time(t_philo *philo)
{
	if (ft_current_time() >= philo->start_time + philo->time_to_die)
	{
		pthread_mutex_lock(&philo->st_death->st_lock);
		philo->status[0] = 1;
		pthread_mutex_unlock(&philo->st_death->st_lock);
		pthread_mutex_lock(&philo->st_death->pt_lock);
		printf("%ld %d died\n", ft_current_time(), philo->id);
		pthread_mutex_unlock(&philo->st_death->pt_lock);
		return (1);
	}
	return (0);
}
