/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcara- <aalcara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:24:50 by coder             #+#    #+#             */
/*   Updated: 2021/11/17 11:47:32 by aalcara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_status(t_philo *philo, char *status)
{
	long long int	elapsed;

	if (philo->dinner->end)
		return (FALSE);
	pthread_mutex_lock(&philo->dinner->mutex.text);
	elapsed = get_current_time() - philo->dinner->start_time;
	printf("%-10lld ", elapsed);
	printf("%-5d %s\n", philo->index, status);
	if (ft_strcmp(status, EAT) == 0)
		philo->last_meal = elapsed;
	pthread_mutex_unlock(&philo->dinner->mutex.text);
	return (TRUE);
}

void	take_forks(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	if (philo->index % 2 == 1 && philo->index != philo->dinner->args.num_philos)
	{
		first_fork = philo->hand[1];
		second_fork = philo->hand[0];
	}
	else
	{
		usleep(EVEN_DELAY);
		first_fork = philo->hand[0];
		second_fork = philo->hand[1];
	}
	pthread_mutex_lock(&philo->dinner->mutex.fork[first_fork]);
	pthread_mutex_lock(&philo->dinner->mutex.fork[second_fork]);
	print_status(philo, FORK);
	print_status(philo, FORK);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->dinner->mutex.fork[philo->hand[0]]);
	pthread_mutex_unlock(&philo->dinner->mutex.fork[philo->hand[1]]);
	philo->eaten_times++;
}

void	do_act(long long int time)
{
	usleep(time * 1000);
}
