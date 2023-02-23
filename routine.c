/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:57:12 by melkholy          #+#    #+#             */
/*   Updated: 2023/02/17 19:15:56 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_one_philo(t_philo *philo)
{
	if (philo->spoon->next)
		return (1);
	printf("%ld %d has taken a fork\n", ft_current_time(), philo->id);
	ft_mysleep(philo, philo->time_to_die);
	return (0);
}

int	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->spoon->lock);
	philo->right_fork = ft_current_time();
	if (ft_one_philo(philo))
		pthread_mutex_lock(&philo->spoon->next->lock);
	philo->left_fork = ft_current_time();
	if (ft_check_status(philo) || ft_check_time(philo))
	{
		pthread_mutex_unlock(&philo->spoon->lock);
		if (philo->spoon->next)
			pthread_mutex_unlock(&philo->spoon->next->lock);
		return (1);
	}
	pthread_mutex_lock(&philo->st_death->pt_lock);
	printf("%ld %d has taken a fork\n", philo->right_fork, philo->id);
	printf("%ld %d has taken a fork\n", philo->left_fork, philo->id);
	printf("%ld %d is eating\n", ft_current_time(), philo->id);
	philo->start_time = ft_current_time();
	pthread_mutex_unlock(&philo->st_death->pt_lock);
	ft_mysleep(philo, philo->time_to_eat);
	pthread_mutex_unlock(&philo->spoon->lock);
	if (philo->spoon->next)
		pthread_mutex_unlock(&philo->spoon->next->lock);
	ft_must_eat(philo);
	return (0);
}

int	ft_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->st_death->pt_lock);
	printf("%ld %d is sleeping\n", ft_current_time(), philo->id);
	pthread_mutex_unlock(&philo->st_death->pt_lock);
	ft_mysleep(philo, philo->time_to_sleep);
	if (ft_check_status(philo) || ft_check_time(philo))
		return (1);
	pthread_mutex_lock(&philo->st_death->pt_lock);
	printf("%ld %d is thinking\n", ft_current_time(), philo->id);
	pthread_mutex_unlock(&philo->st_death->pt_lock);
	if (philo->time_to_eat > philo->time_to_sleep)
		ft_mysleep(philo, 10);
	if (ft_check_status(philo) || ft_check_time(philo))
		return (1);
	return (0);
}

void	*ft_run_time(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(20);
	while (true)
	{
		if (ft_eating(philo))
			return (NULL);
		if (ft_check_status(philo) || ft_check_time(philo))
			return (NULL);
		if (ft_sleeping(philo))
			return (NULL);
	}
	return (NULL);
}
