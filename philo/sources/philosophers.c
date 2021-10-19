/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 20:10:17 by aalcara-          #+#    #+#             */
/*   Updated: 2021/10/19 17:05:33 by coder            ###   ########.fr       */
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


int	main(int argc, char **argv)
{
	t_dinner	dinner;
	
	//TODO ? adicionar verificação do número de philos
	if (check_arguments(argc, argv) != 0)
		return (EXIT_FAILURE);
	dinner.args = convert_args(argv);
	// printf("%d %d %d %d %d\n", dinner.args.num_philos, dinner.args.tm_die, dinner.args.tm_eat, dinner.args.tm_sleep, dinner.args.num_eats);
	if (!init_simulation(&dinner))
		return (EXIT_FAILURE);
	

	
	return (EXIT_SUCCESS);
}