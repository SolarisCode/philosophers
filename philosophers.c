/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:31:48 by melkholy          #+#    #+#             */
/*   Updated: 2023/02/16 20:29:47 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_start_threads(t_philo *philos, int philo_num)
{
	pthread_t	*threads;
	t_philo		*p_tmp;
	int			count;
	long		start_time;

	threads = (pthread_t *)ft_calloc(philo_num, sizeof(pthread_t));
	if (!threads)
		return ;
	p_tmp = philos;
	count = -1;
	start_time = ft_current_time();
	while (++count < philo_num)
	{
		p_tmp->start_time = start_time;
		if (pthread_create(&threads[count], NULL,
				&ft_run_time, (void *)(p_tmp)))
			return ;
		p_tmp = p_tmp->next;
	}
	while (--count >= 0)
		pthread_join(*(threads + count), NULL);
	while (++count < philo_num)
		pthread_detach(threads[count]);
	free(threads);
}

void	ft_destroy_threads(t_philo **philos, t_fork **spoons, int philo_num)
{
	t_philo	*p_tmp;
	t_fork	*f_tmp;
	int		count;

	count = 0;
	p_tmp = *philos;
	f_tmp = *spoons;
	pthread_mutex_destroy(&(*philos)->st_death->st_lock);
	pthread_mutex_destroy(&(*philos)->st_death->pt_lock);
	while (count < philo_num)
	{
		if ((*spoons))
			pthread_mutex_destroy(&(*spoons)->lock);
		*philos = (*philos)->next;
		*spoons = (*spoons)->next;
		free(p_tmp);
		free(f_tmp);
		p_tmp = *philos;
		f_tmp = *spoons;
		count ++;
	}
}

int	main(int argc, char *argv[])
{
	t_input	*in_data;
	t_philo	*philos;
	t_fork	*spoons;
	int		*status;

	if (argc < 5)
		return (1);
	else if (!ft_check_nbr(&argv[1]))
		return (1);
	in_data = (t_input *)ft_calloc(1, sizeof(t_input));
	ft_create_input(in_data, &argv[1]);
	status = (int *)ft_calloc(2, sizeof(int));
	philos = ft_create_philos(in_data);
	spoons = ft_create_forks(in_data->number_of_philo);
	ft_init_philos(philos, spoons, status, in_data->number_of_philo);
	ft_start_threads(philos, in_data->number_of_philo);
	ft_destroy_threads(&philos, &spoons, in_data->number_of_philo);
	free(in_data);
	free(status);
}
