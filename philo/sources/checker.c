/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcara- <aalcara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 20:10:17 by aalcara-          #+#    #+#             */
/*   Updated: 2021/09/24 23:13:37 by aalcara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
		{
			if (i != 0)
				return (EXIT_FAILURE);
			else
				if (str[i] != '-')
					return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	check_num_of_args(int argc)
{
	if (argc < MIN_ARGS || argc > MAX_ARGS)
	{
		printf("%s\n%s\n", WRONG_NUM_ARGS, USAGE);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	check_biger_zero(char *str)
{
	int number;

	number = ft_atoi(str);
	if (number <= 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_arguments(int argc, char **argv)
{
	int	i;

	i = 1;
	if (check_num_of_args(argc))
		return (EXIT_FAILURE);
	while (argv[i] != NULL)
	{
		if (check_is_number(argv[i]))
		{
			printf("%s\n", USAGE);
			return (EXIT_FAILURE);
		}
		if (check_biger_zero(argv[i]))
		{
			printf("%s\n", BIGGER_THAN_ZERO);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
