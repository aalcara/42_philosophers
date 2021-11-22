/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcara- <aalcara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:24:50 by coder             #+#    #+#             */
/*   Updated: 2021/11/22 02:12:58 by aalcara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_status(t_philo *philo, char *status)
{
	long long int	elapsed;

	if (philo->dinner->end)
		return (FALSE);
	sem_wait(philo->dinner->semaphores.text);
	elapsed = get_current_time() - philo->dinner->start_time;
	printf("%lld %d %s\n",elapsed, philo->index, status);
	if (ft_strcmp(status, EAT) == 0)
		philo->last_meal = elapsed;
	sem_post(philo->dinner->semaphores.text);
	return (TRUE);
}

void	take_forks(t_philo *philo)
{
	sem_wait(philo->dinner->semaphores.forks);
	sem_wait(philo->dinner->semaphores.forks);
	print_status(philo, FORK);
	print_status(philo, FORK);
}

void	drop_forks(t_philo *philo)
{
	sem_post(philo->dinner->semaphores.forks);
	sem_post(philo->dinner->semaphores.forks);
	philo->eaten_times++;
}

void	do_act(long long int time)
{
	usleep(time * 1000);
}
