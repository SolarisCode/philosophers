/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:52:10 by melkholy          #+#    #+#             */
/*   Updated: 2023/02/16 20:30:00 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;
	int		count;

	count = 0;
	array = malloc(nmemb * size);
	if (!array)
		return (NULL);
	memset(array, 0, nmemb * size);
	return (array);
}

t_philo	*ft_philo_new(t_input *in_data)
{
	t_philo	*new;

	new = (t_philo *)ft_calloc(1, sizeof(t_philo));
	if (!new)
		return (NULL);
	new->time_to_die = in_data->time_to_die;
	new->time_to_eat = in_data->time_to_eat;
	new->time_to_sleep = in_data->time_to_sleep;
	new->number_must_eat = in_data->number_must_eat;
	new->num_philo = in_data->number_of_philo;
	new->next = NULL;
	return (new);
}

int	ft_atoi(const char *str)
{
	int	count;
	int	val;
	int	sign;

	count = 0;
	val = 0;
	sign = 1;
	while ((str[count] >= 9 && str[count] <= 13) || str[count] == 32)
		count ++;
	if (str[count] == '-' || str[count] == '+')
	{
		if (str[count] == '-')
			sign *= -1;
		count ++;
	}
	while (str[count] && str[count] >= 48 && str[count] <= 57)
	{
		val = (val * 10) + (str[count] - 48);
		count ++;
	}
	return (val * sign);
}

int	ft_isdigit(int x)
{
	if (x >= '0' && x <= '9')
		return (1);
	else
		return (0);
}

bool	ft_check_nbr(char **argv)
{
	int	count;
	int	index;

	count = -1;
	while (argv[++count])
	{
		index = -1;
		if (argv[count][0] == '-' && argv[count][1])
			return (write(1, "Please enter postive numbers!\n", 30), false);
		if (argv[count][0] == '+' && argv[count][1])
			index ++;
		while (argv[count][++index])
			if (!ft_isdigit(argv[count][index]))
				return (write(1, "Please enter only numbers!\n", 27), false);
	}
	if (!ft_atoi(argv[0]))
		return (write(1, "Philosophers can't be 0!\n", 25), false);
	return (true);
}
