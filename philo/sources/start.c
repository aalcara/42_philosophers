/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcara- <aalcara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:24:50 by coder             #+#    #+#             */
/*   Updated: 2021/10/26 17:20:48 by aalcara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	create_threads(int total, t_philo *philo, pthread_t *thread)
{
	int	i;

	i = 0;
	while (++i <= total)
	{
		if (pthread_create(&thread[i - 1], NULL, &routine, &philo[i]))
		{
			printf("%s\n", THREAD_CREATE);
			return (false);
		}
	}
	return (true);
}

static bool	join_threads(int total, pthread_t *thread)
{
	int	i;

	i = 0;
	while (++i <= total)
	{
		if (pthread_join(thread[i - 1], NULL))
		{
			printf("%s\n", THREAD_JOIN);
			return (false);
		}
	}
	return (true);
}

bool	start_simulation(t_dinner *dinner, t_philo *philo)
{
	pthread_t	philo_treads[MAX_NUM_PHILOS];

	dinner->start_time = get_current_time();
	if (!create_threads(dinner->args.num_philos, philo, philo_treads))
		return (false);
	if (!join_threads(dinner->args.num_philos, philo_treads))
		return (false);
	return (true);
}
