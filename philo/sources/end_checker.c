/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcara- <aalcara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:24:50 by coder             #+#    #+#             */
/*   Updated: 2021/10/23 11:28:10 by aalcara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// bool	define_death(t_philo *philo, long long int elapsed)----------------------
// {
// 	pthread_mutex_lock(&philo->dinner->mutex.death);
// 	philo->dinner->end = philo->index;
// 	philo->dinner->tm_of_death = elapsed;
// 	pthread_mutex_unlock(&philo->dinner->mutex.death);
// 	return (true);
// }
// -- verify end

static bool	ended(t_philo *philo)
{
	long long int	elapsed;

	if (philo->dinner->end)
		return (true);
	if (philo->dinner->args.num_eats)
		if (philo->eaten_times >= philo->dinner->args.num_eats)
			return (true);
	elapsed = get_current_time() - philo->dinner->start_time;
	if ((elapsed - philo->last_meal) > philo->dinner->args.tm_die)
	{
		pthread_mutex_lock(&philo->dinner->mutex.death);
		philo->dinner->end = philo->index;
		philo->dinner->tm_of_death = elapsed;
		pthread_mutex_unlock(&philo->dinner->mutex.death);
		return (true);
	}
	return (false);
}

void	*verify_end_conditions(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	while (!ended(philo))
		continue ;
	return (NULL);
}
