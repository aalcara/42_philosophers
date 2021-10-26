/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcara- <aalcara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:24:50 by coder             #+#    #+#             */
/*   Updated: 2021/10/23 11:24:55 by aalcara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool print_status(t_philo *philo, char *status)
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

bool	eat(t_philo *philo)
{
	take_forks(philo);
	if (!print_status(philo, EAT))
		return (false);
	do_act(philo->dinner->args.tm_eat);
	drop_forks(philo);
	if (philo->dinner->args.num_eats)
		if (philo->eaten_times >= philo->dinner->args.num_eats)
			return (false);
	return (true);
}

bool	sleeping(t_philo *philo)
{
	if (!print_status(philo, SLEEP))
		return (false);
	do_act(philo->dinner->args.tm_sleep);
	return (true);
}

bool	think(t_philo *philo)
{
	if (!print_status(philo, THINK))
		return (false);
	return (true);
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;
	pthread_t end_searcher;

	philo = (t_philo *)philo_ptr;
	if (philo->index % 2 == 0)
		usleep(EVEN_DELAY);
	pthread_create(&end_searcher, NULL, verify_end_conditions, philo);
	pthread_detach(end_searcher);
	while (eat(philo) && sleeping(philo) && think(philo))
		continue ;
	return (NULL);
}
