/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:25:13 by coder             #+#    #+#             */
/*   Updated: 2021/10/19 17:26:28 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	define_forks_index(t_philo *philo, int index, int last_philo)
{
	philo[index].hand[0] = index;
	philo[index].hand[1] = index + 1;
	if (index == last_philo)
		philo[index].hand[1] = 1;
}

static void	init_mutex(t_dinner *dinner)
{
	t_mutex	*mutex;
	int		total;
	int		i;
	
	i = 0;
	mutex = &dinner->mutex;
	total = dinner->args.num_philos;
	while (i++ <= total)
		pthread_mutex_init(&mutex->fork[i], NULL);
	pthread_mutex_init(&mutex->text, NULL);
	pthread_mutex_init(&mutex->death, NULL);
}

static void	init_philos(t_philo *philo, t_dinner *dinner, int i)
{
	int	total;

	total = dinner->args.num_philos;
	while (++i <= total)
	{
		ft_bzero(&philo[i], sizeof(t_philo));
		philo[i].index = i;
		define_forks_index(philo, i, total);
		philo[i].dinner = dinner;
	}
}

static bool	check_only_one_philo(t_dinner *dinner)
{
	if (dinner->args.num_philos == 1)
	{
		printf("%-10d %-3d %-20s\n", 0, 1, FORK);
		dinner->tm_of_death = dinner->args.tm_die + 1;
		dinner->end = 1;
		usleep(dinner->args.tm_die * 1000);
		return (true);
	}
	return (false);
}

bool	init_simulation(t_dinner *dinner)
{
	t_philo	philo[MAX_NUM_PHILOS + 2];

	init_philos(philo, dinner, 0);
	init_mutex(dinner);
	if (check_only_one_philo(dinner))
		return (true);
	if (!start_simulation(dinner, philo))
		return (false);
	return (true);
}
