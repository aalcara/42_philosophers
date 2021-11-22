/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcara- <aalcara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:24:50 by coder             #+#    #+#             */
/*   Updated: 2021/11/22 18:29:27 by aalcara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eat(t_philo *philo)
{
	usleep(FORK_DELAY);
	take_forks(philo);
	if (!print_status(philo, EAT))
	{
		drop_forks(philo);
		return (FALSE);
	}
	do_act(philo->dinner->args.tm_eat);
	drop_forks(philo);
	if (philo->dinner->args.num_eats)
		if (philo->eaten_times >= philo->dinner->args.num_eats)
			return (FALSE);
	return (TRUE);
}

static int	sleeping(t_philo *philo)
{
	if (!print_status(philo, SLEEP))
		return (FALSE);
	do_act(philo->dinner->args.tm_sleep);
	return (TRUE);
}

static int	think(t_philo *philo)
{
	if (!print_status(philo, THINK))
		return (FALSE);
	return (TRUE);
}

void	*routine(t_philo *philo)
{
	pthread_t	end_searcher;

	if (philo->index % 2 == 0)
		usleep(EVEN_DELAY);
	pthread_create(&end_searcher, NULL, verify_end_conditions, philo);
	pthread_detach(end_searcher);
	while (eat(philo) && sleeping(philo) && think(philo))
		continue ;
	return (0);
}
