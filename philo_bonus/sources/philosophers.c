/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcara- <aalcara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 20:10:17 by aalcara-          #+#    #+#             */
/*   Updated: 2021/11/22 13:49:02 by aalcara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_args	convert_args(char **argv)
{
	t_args	args;

	args.num_philos = ft_atoi(argv[1]);
	args.tm_die = ft_atoi(argv[2]);
	args.tm_eat = ft_atoi(argv[3]);
	args.tm_sleep = ft_atoi(argv[4]);
	if (argv[5])
		args.num_eats = ft_atoi(argv[5]);
	else
		args.num_eats = 0;
	return (args);
}

static void	close_semaphores(t_semaphores *semaphores)
{
	sem_unlink("forks");
	sem_unlink("text");
	sem_unlink("death");
	sem_unlink("finish");
	sem_unlink("satisfied");
	sem_close(semaphores->forks);
	sem_close(semaphores->text);
	sem_close(semaphores->death);
	sem_close(semaphores->finish);
	sem_close(semaphores->satisfied);
}

int	main(int argc, char **argv)
{
	t_dinner	*dinner;

	dinner = (t_dinner *)malloc(sizeof(t_dinner));
	memset(dinner, 0, sizeof(t_dinner));
	if (check_arguments(argc, argv) != 0)
		return (EXIT_FAILURE);
	dinner->args = convert_args(argv);
	if (!init_simulation(dinner))
		return (EXIT_FAILURE);
	close_semaphores(&dinner->semaphores);
	kill(0, SIGINT);
}
