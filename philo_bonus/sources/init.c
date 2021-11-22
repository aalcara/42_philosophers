/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcara- <aalcara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:25:13 by coder             #+#    #+#             */
/*   Updated: 2021/11/22 18:51:07 by aalcara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_semaphores(t_dinner *dinner)
{
	t_semaphores	*semaphores;
	int				total;

	total = dinner->args.num_philos;
	semaphores = &dinner->semaphores;
	sem_unlink("forks");
	sem_unlink("text");
	sem_unlink("death");
	sem_unlink("finish");
	sem_unlink("satisfied");
	semaphores->forks = sem_open("forks", O_CREAT | O_EXCL, 0777, total / 2);
	semaphores->text = sem_open("text", O_CREAT | O_EXCL, 0777, 1);
	semaphores->death = sem_open("death", O_CREAT | O_EXCL, 0777, 1);
	semaphores->finish = sem_open("finish", O_CREAT | O_EXCL, 0777, 0);
	semaphores->satisfied = sem_open("satisfied", O_CREAT | O_EXCL, 0777, 0);
}

static int	check_only_one_philo(t_dinner *dinner)
{
	if (dinner->args.num_philos == 1)
	{
		printf("%d %d %s\n", 0, 1, FORK);
		dinner->tm_of_death = dinner->args.tm_die + 1;
		dinner->end = 1;
		usleep(dinner->args.tm_die * 1000);
		return (TRUE);
	}
	return (FALSE);
}

int	init_simulation(t_dinner *dinner)
{
	t_philo	philo[MAX_NUM_PHILOS + 2];
	int		total;
	int		i;

	i = 0;
	total = dinner->args.num_philos;
	while (++i <= total)
	{
		philo[i].index = i;
		philo[i].dinner = dinner;
	}
	init_semaphores(dinner);
	if (check_only_one_philo(dinner))
		return (TRUE);
	if (!start_simulation(dinner, philo))
		return (FALSE);
	return (TRUE);
}
