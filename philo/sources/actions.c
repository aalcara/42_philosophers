/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcara- <aalcara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:24:50 by coder             #+#    #+#             */
/*   Updated: 2021/10/26 17:33:46 by aalcara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	print_status(t_philo *philo, char *status)
{
	long long int	elapsed;

	if (philo->dinner->end)
		return (false);
	pthread_mutex_lock(&philo->dinner->mutex.text);
	elapsed = get_current_time() - philo->dinner->start_time;
	printf("%-10lld ", elapsed);
	printf("%-5d %s\n", philo->index, status);
	if (ft_strcmp(status, EAT) == 0)
		philo->last_meal = elapsed;
	pthread_mutex_unlock(&philo->dinner->mutex.text);
	return (true);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->mutex.fork[philo->hand[0]]);
	print_status(philo, FORK);
	pthread_mutex_lock(&philo->dinner->mutex.fork[philo->hand[1]]);
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
