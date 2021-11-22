/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcara- <aalcara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:25:13 by coder             #+#    #+#             */
/*   Updated: 2021/11/22 02:05:39 by aalcara-         ###   ########.fr       */
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
	semaphores->forks = sem_open("forks", SEM_FLAGS, SEM_PERM, total);
	semaphores->text = sem_open("text", SEM_FLAGS, SEM_PERM, 1);
	semaphores->death = sem_open("death", SEM_FLAGS, SEM_PERM, 1);
	semaphores->finish = sem_open("finish", SEM_FLAGS, SEM_PERM, 0);
	semaphores->satisfied = sem_open("satisfied", SEM_FLAGS, SEM_PERM, 0);

}

// static void	init_philos(t_philo *philo, t_dinner *dinner)
// {
// 	int	total;
// 	int i;

// 	i = 0;
// 	total = dinner->args.num_philos;
// 	while (++i <= total)
// 	{
// 		// ft_bzero(&philo[i], sizeof(t_philo));
// 		philo[i].index = i;
// 		philo[i].dinner = dinner;
// 		// printf("1dinner = %d\n", philo[i].dinner->args.tm_die);
		
// 	}
// }

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

	// init_philos(&philo[0], dinner);
	int	total;
	int i;

	i = 0;
	total = dinner->args.num_philos;
	while (++i <= total)
	{
		// ft_bzero(&philo[i], sizeof(t_philo));
		philo[i].index = i;
		philo[i].dinner = dinner;
		// printf("1dinner = %d\n", philo[i].dinner->args.tm_die);
		
	}

	// printf("2dinner = %d\n", philo[1].dinner->args.tm_die);//
	init_semaphores(dinner);
	if (check_only_one_philo(dinner))
		return (TRUE);
	if (!start_simulation(dinner, philo))
		return (FALSE);
	// printf("4time of death = %lld\n", dinner->tm_of_death);
	return (TRUE);
}
