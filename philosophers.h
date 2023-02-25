/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:01:19 by melkholy          #+#    #+#             */
/*   Updated: 2023/02/16 21:00:36 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_input
{
	long	number_of_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		number_must_eat;
}				t_input;

typedef struct s_death
{
	pthread_mutex_t	st_lock;
	pthread_mutex_t	pt_lock;
}				t_death;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	lock;
	struct s_fork	*next;
}				t_fork;

typedef struct s_philo
{
	int				id;
	int				*status;
	int				num_philo;
	int				number_must_eat;
	int				eat_count;
	long			right_fork;
	long			left_fork;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	t_fork			*spoon;
	t_death			*st_death;
	struct s_philo	*next;
}				t_philo;

/*	philosophers.c	*/
void	ft_destroy_threads(t_philo **philos, t_fork **spoons, int philo_num);
void	ft_start_threads(t_philo *philos, int philo_num);

/*	helper.c	*/
void	*ft_calloc(size_t nmemb, size_t size);
t_philo	*ft_philo_new(t_input *in_data);
int		ft_atoi(const char *str);
int		ft_isdigit(int x);
bool	ft_check_nbr(char **argv);

/*	utils.c	*/
t_fork	*ft_create_forks(int fork_num);
t_philo	*ft_create_philos(t_input *in_data);
void	ft_create_input(t_input *in_data, char **argv);
long	ft_current_time(void);
void	ft_init_philos(t_philo *philos, t_fork *spoons, int *status,
			int philo_num);

/*	routine.c	*/
int		ft_one_philo(t_philo *philo);
int		ft_eating(t_philo *philo);
int		ft_sleeping(t_philo *philo);
void	*ft_run_time(void *arg);

/* status_time_check.c	*/
void	ft_must_eat(t_philo *philo);
int		ft_check_status(t_philo *philo);
void	ft_pa_death(t_philo *philo);
void	ft_mysleep(t_philo *philo, long millisecond);
int		ft_check_time(t_philo *philo);

#endif
