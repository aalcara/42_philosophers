/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcara- <aalcara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 20:10:17 by aalcara-          #+#    #+#             */
/*   Updated: 2021/11/17 14:38:01 by aalcara-         ###   ########.fr       */
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

static void	print_end_message(t_dinner *dinner)
{
	if (dinner->tm_of_death)
		printf("%lld %d %s\n", dinner->tm_of_death, dinner->end, DIE);
	else
		printf("Philosophers ate %d times!\n", dinner->args.num_eats);
}

static void	destroy_mutexes(t_mutex *mutex, int total)
{
	int	i;

	i = 0;
	while (i++ <= total)
		pthread_mutex_destroy(&mutex->fork[i]);
	pthread_mutex_destroy(&mutex->text);
	pthread_mutex_destroy(&mutex->death);
}

int	main(int argc, char **argv)
{
	t_dinner	dinner;

	if (check_arguments(argc, argv) != 0)
		return (EXIT_FAILURE);
	dinner.args = convert_args(argv);
	if (!init_simulation(&dinner))
		return (EXIT_FAILURE);
	print_end_message(&dinner);
	destroy_mutexes(&dinner.mutex, dinner.args.num_philos);
	return (EXIT_SUCCESS);
}
