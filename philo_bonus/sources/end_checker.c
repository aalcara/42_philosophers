/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcara- <aalcara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:24:50 by coder             #+#    #+#             */
/*   Updated: 2021/11/22 01:48:03 by aalcara-         ###   ########.fr       */
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
			// printf("[%d] comeu tudo\n\n", philo->index);//
			sem_post(philo->dinner->semaphores.satisfied);
			return (TRUE);
			
		}
	}
	elapsed = get_current_time() - philo->dinner->start_time;
	// printf("%d = %lld - %lld > %d\n", philo->index, elapsed, philo->last_meal, philo->dinner->args.tm_die);//
	if ((elapsed - philo->last_meal) > philo->dinner->args.tm_die)
	{
		// pthread_mutex_lock(&philo->dinner->mutex.death);
		sem_wait(philo->dinner->semaphores.death);
		
		print_status(philo, DIE);
		sem_post(philo->dinner->semaphores.finish);
		// sem_post(philo->dinner->semaphores.death);
		// pthread_mutex_unlock(&philo->dinner->mutex.death);
		sem_post(philo->dinner->semaphores.death);
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
	// printf("%d = %d - %lld\n", philo->index, philo->dinner->end, philo->dinner->tm_of_death);//
	// return (NULL);
	exit(0);
}
