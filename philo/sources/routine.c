/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcara- <aalcara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:24:50 by coder             #+#    #+#             */
/*   Updated: 2021/11/17 11:07:46 by aalcara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eat(t_philo *philo)
{
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

void	*routine(void *philo_ptr)
{
	t_philo		*philo;
	pthread_t	end_searcher;

	philo = (t_philo *)philo_ptr;
	if (philo->index % 2 == 0)
		usleep(EVEN_DELAY);
	pthread_create(&end_searcher, NULL, verify_end_conditions, philo);
	pthread_detach(end_searcher);
	while (eat(philo) && sleeping(philo) && think(philo))
		continue ;
	return (NULL);
}
