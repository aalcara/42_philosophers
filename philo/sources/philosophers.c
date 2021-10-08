/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcara- <aalcara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 20:10:17 by aalcara-          #+#    #+#             */
/*   Updated: 2021/10/06 17:09:54 by aalcara-         ###   ########.fr       */
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

void	plance_a_philo(int num)
{
	pthread_t *philo;

	
}

void	start_simulation(t_args args)
{
	int i;

	i = 0;
	while (i < args.num_philos)
	{
		place_a_philo(i);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_args	args;
	
	if (check_arguments(argc, argv) != 0)
		return (EXIT_FAILURE);
	args = convert_args(argv);
	printf("%d %d %d %d %d\n", args.num_philos, args.tm_die, args.tm_eat, args.tm_sleep, args.num_eats);
	start_simulation(args);

	
	return (EXIT_SUCCESS);
}