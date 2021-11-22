/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcara- <aalcara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 20:10:17 by aalcara-          #+#    #+#             */
/*   Updated: 2021/11/22 02:05:35 by aalcara-         ###   ########.fr       */
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

// static void	print_end_message(t_dinner *dinner)
// {
// 	if (dinner->tm_of_death != 0)
// 		printf("%lld %d %s\n", dinner->tm_of_death, dinner->end, DIE);
// 	else
// 		printf("Philosophers ate %d times!\n", dinner->args.num_eats);
// }

static void	close_semaphores(t_semaphores *semaphores)
{
	// int	i;

	// i = 0;
	// while (i++ <= total)
	// 	pthread_mutex_destroy(&mutex->fork[i]);
	// pthread_mutex_destroy(&mutex->text);
	// pthread_mutex_destroy(&mutex->death);
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

	// ft_bzero(&dinner, sizeof(t_dinner));
	// dinner.end = 0;
	// dinner.satisfied_philos = 0;
	// dinner.tm_of_death = 0;

	dinner = (t_dinner *)malloc(sizeof(t_dinner));
	// printf("1time of death = %lld\n", dinner->tm_of_death);//
	memset(dinner, 0, sizeof(t_dinner));

	// printf("2time of death = %lld\n", dinner->tm_of_death);//
	// printf("dinner.end = [%d]", dinner.end);
	if (check_arguments(argc, argv) != 0)
		return (EXIT_FAILURE);
	dinner->args = convert_args(argv);
	if (!init_simulation(dinner))
		return (EXIT_FAILURE);
	// print_end_message(dinner);
	close_semaphores(&dinner->semaphores);
	// printf("3time of death = %lld\n", dinner->tm_of_death);//
	kill(0, SIGINT);
	// return (EXIT_SUCCESS);
}
