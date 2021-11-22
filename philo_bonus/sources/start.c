/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcara- <aalcara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:24:50 by coder             #+#    #+#             */
/*   Updated: 2021/11/22 13:49:47 by aalcara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_philos(t_dinner *dinner, t_philo *philo, pid_t *pid)
{
	int	i;
	int	total;

	i = 0;
	total = dinner->args.num_philos;
	while (++i <= total)
	{
		pid[i - 1] = fork();
		if (pid[i - 1] < 0)
		{
			printf("%s\n", ERR_CREATE_PHILO);
			return (FALSE);
		}
		if (pid[i - 1] == 0)
		{
			routine(philo + i);
			exit(0);
		}
	}
	return (TRUE);
}

static int	wait_philo_die(t_dinner *dinner, pid_t *pid)
{
	int	i;
	int	waiter;
	int	total;

	total = dinner->args.num_philos;
	i = 0;
	waiter = sem_wait(dinner->semaphores.finish);
	if (waiter == -1)
		printf(ERR_WAIT);
	while (++i <= total)
		kill(pid[i - 1], SIGKILL);
	return (TRUE);
}

static int	wait_philo_eat(t_dinner *dinner)
{
	pid_t	waiter;
	int		status;
	int		total;
	int		i;

	total = dinner->args.num_philos;
	i = 0;
	sem_wait(dinner->semaphores.satisfied);
	while (++i <= total)
		waiter = waitpid(-1, &status, 0);
	printf("Philosophers ate %d times!\n", dinner->args.num_eats);
	return (TRUE);
}

int	start_simulation(t_dinner *dinner, t_philo *philo)
{
	pid_t	philo_pids[MAX_NUM_PHILOS];
	pid_t	checker;

	dinner->start_time = get_current_time();
	if (!create_philos(dinner, philo, philo_pids))
		return (FALSE);
	checker = fork();
	if (checker == 0)
		wait_philo_die(dinner, philo_pids);
	if (checker != 0)
		wait_philo_eat(dinner);
	return (TRUE);
}
