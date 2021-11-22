/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcara- <aalcara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:24:50 by coder             #+#    #+#             */
/*   Updated: 2021/11/22 02:13:29 by aalcara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static int	create_threads(int total, t_philo *philo, pthread_t *thread)
// {
// 	int	i;

// 	i = 0;
// 	while (++i <= total)
// 	{
// 		if (pthread_create(&thread[i - 1], NULL, &routine, &philo[i]))
// 		{
// 			printf("%s\n", THREAD_CREATE);
// 			return (FALSE);
// 		}
// 	}
// 	return (TRUE);
// }

static int	create_philos(t_dinner *dinner, t_philo *philo, pid_t *pid)
{
	int i;
	int total;

	i = 0;
	total = dinner->args.num_philos;
	// printf("7time of death = %lld\n", philo[0].dinner->tm_of_death);
	while (++i <= total)
	{
		pid[i - 1] = fork();
		if (pid[i - 1] < 0)
		{
			printf("%s\n",ERR_CREATE_PHILO);
			return (FALSE);
		}
		if (pid[i - 1] == 0)
		{
			routine(philo + i);
			// printf("9time of death = %lld\n", (philo + i)->dinner->tm_of_death);
			exit(0);
		}
	}
	// printf("9time of death = %lld\n", philo[1].dinner->tm_of_death);
	return (TRUE);
}

static int	wait_philo_die(t_dinner *dinner, pid_t *pid)
{
	int		i;
	// pid_t	waiter;
	// int		status;
	int		total;

	total = dinner->args.num_philos;
	i = 0;
	sem_wait(dinner->semaphores.finish);
	// waiter = waitpid(-1, &status, 0);
	// 	if (WIFEXITED(status))
	// 		printf("Child %d terminated with status: %d. [%d]\n",waiter, WEXITSTATUS(status), getpid()); //!corrigir
	while (++i <= total)
	{
		// printf("pid[%d] = %d\n", i, pid[i - 1]);
		kill(pid[i - 1], SIGKILL);
	}
	// kill(0, SIGINT);
	

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
	{
		waiter = waitpid(-1, &status, 0);
		// if (WIFEXITED(status))
		// 	printf("Child %d terminated with status: %d. [%d]\n",waiter, WEXITSTATUS(status), getpid()); //!corrigir
	}
	printf("Philosophers ate %d times!\n", dinner->args.num_eats);
	return (TRUE);
}

int	start_simulation(t_dinner *dinner, t_philo *philo)
{
	// pthread_t	philo_treads[MAX_NUM_PHILOS];
	pid_t	philo_pids[MAX_NUM_PHILOS];
	pid_t	checker;

	dinner->start_time = get_current_time();
	// if (!create_threads(dinner->args.num_philos, philo, philo_treads))
	// printf("5time of death = %lld\n", dinner->tm_of_death);
	if (!create_philos(dinner, philo, philo_pids))
		return (FALSE);
	// if (!join_threads(dinner->args.num_philos, philo_treads))
	// printf("11time of death = %lld\n", dinner->tm_of_death);
	checker = fork();
	if (checker == 0)
		wait_philo_die(dinner, philo_pids);
	if (checker != 0)
		wait_philo_eat(dinner);
	// printf("6time of death = %lld\n", dinner->tm_of_death);
	return (TRUE);
}
