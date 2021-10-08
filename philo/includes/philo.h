/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcara- <aalcara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 20:34:59 by aalcara-          #+#    #+#             */
/*   Updated: 2021/09/28 00:02:26 by aalcara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H
# define MIN_ARGS 5
# define MAX_ARGS 6

# define WRONG_NUM_ARGS "Wrong number of arguments!"
# define BIGGER_THAN_ZERO "Use numbers biggers than zero!"
# define USAGE "Usage: ./philo n_philo ms_to_die ms_to_eat _ms_to_sleep [n_eat]" 

# include <stdio.h> //printf
# include <stdlib.h> //exit_return
# include <pthread.h>

typedef struct s_args
{
	int	num_philos;
	int	tm_die;
	int	tm_eat;
	int	tm_sleep;
	int	num_eats;
} t_args;

// checker
int	check_arguments(int argc, char **argv);

// utils
int	ft_atoi(const char *nptr);

#endif