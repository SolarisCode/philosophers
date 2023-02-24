/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:54:13 by melkholy          #+#    #+#             */
/*   Updated: 2023/02/16 20:30:39 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_current_time(void)
{
	struct timeval	tp;
	long			milisecond;

	gettimeofday(&tp, NULL);
	milisecond = tp.tv_sec * 1000;
	milisecond += tp.tv_usec / 1000;
	return (milisecond);
}

void	ft_init_philos(t_philo *philos, t_fork *spoons, int *status,
		int philo_num)
{
	t_philo			*p_tmp;
	t_fork			*f_tmp;
	t_death			*death;
	int				count;

	count = -1;
	death = (t_death *)ft_calloc(1, sizeof(t_death));
	pthread_mutex_init(&death->st_lock, NULL);
	pthread_mutex_init(&death->pt_lock, NULL);
	f_tmp = spoons;
	p_tmp = philos;
	while (++count < philo_num)
	{
		pthread_mutex_init(&f_tmp->lock, NULL);
		p_tmp->spoon = f_tmp;
		p_tmp->status = status;
		p_tmp->st_death = death;
		f_tmp = f_tmp->next;
		p_tmp = p_tmp->next;
	}
}

t_fork	*ft_create_forks(int fork_num)
{
	t_fork	*spoons;
	t_fork	*s_tmp;
	int		count;

	count = 1;
	spoons = (t_fork *)ft_calloc(1, sizeof(t_fork));
	spoons->id = count;
	spoons->next = NULL;
	s_tmp = spoons;
	while (count < fork_num)
	{
		s_tmp->next = (t_fork *)ft_calloc(1, sizeof(t_fork));
		count ++;
		s_tmp = s_tmp->next;
		s_tmp->id = count;
	}
	if (fork_num != 1)
		s_tmp->next = spoons;
	return (spoons);
}

t_philo	*ft_create_philos(t_input *in_data)
{
	t_philo	*head;
	t_philo	*p_tmp;
	int		count;

	count = 1;
	head = ft_philo_new(in_data);
	head->id = count;
	p_tmp = head;
	while (count < in_data->number_of_philo)
	{
		p_tmp->next = ft_philo_new(in_data);
		count ++;
		p_tmp = p_tmp->next;
		p_tmp->id = count;
	}
	if (in_data->number_of_philo != 1)
		p_tmp->next = head;
	return (head);
}

void	ft_create_input(t_input *in_data, char **argv)
{
	in_data->number_of_philo = ft_atoi(argv[0]);
	in_data->time_to_die = ft_atoi(argv[1]);
	in_data->time_to_eat = ft_atoi(argv[2]);
	in_data->time_to_sleep = ft_atoi(argv[3]);
	if (argv[4])
		in_data->number_must_eat = ft_atoi(argv[4]);
	else
		in_data->number_must_eat = -1;
}
