/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcara- <aalcara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:24:50 by coder             #+#    #+#             */
/*   Updated: 2021/11/22 18:01:19 by aalcara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ended(t_philo *philo)
{
	long long int	elapsed;

	if (philo->dinner->end)
		return (TRUE);
	if (philo->dinner->args.num_eats)
	{
		if (philo->eaten_times >= philo->dinner->args.num_eats)
		{
			sem_post(philo->dinner->semaphores.satisfied);
			return (TRUE);
		}
	}
	elapsed = get_current_time() - philo->dinner->start_time;
	if ((elapsed - philo->last_meal) > philo->dinner->args.tm_die)
	{
		sem_wait(philo->dinner->semaphores.death);
		print_status(philo, DIE);
		sem_post(philo->dinner->semaphores.finish);
		sem_post(philo->dinner->semaphores.death);
		exit(0);
		return (TRUE);
	}
	return (FALSE);
}

void	*verify_end_conditions(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	while (!ended(philo))
		continue ;
	exit(0);
}
