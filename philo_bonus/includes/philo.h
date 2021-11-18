/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcara- <aalcara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 20:34:59 by aalcara-          #+#    #+#             */
/*   Updated: 2021/11/18 07:39:14 by aalcara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define MIN_ARGS 5
# define MAX_ARGS 6
# define MAX_NUM_PHILOS 1000
# define EVEN_DELAY 6000
# define TRUE 1
# define FALSE 0
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

# define MAX_PHILOS_ERROR "Don't run with more than 1000 philos!"
# define WRONG_NUM_ARGS "Wrong number of arguments!"
# define BIGGER_THAN_ZERO "Use numbers biggers than zero!"
# define USAGE "Usage:./philo n_philo ms_to_die ms_to_eat _ms_to_sleep [n_eat]" 
# define THREAD_CREATE "Error creating thread" 
# define THREAD_JOIN "Error joining thread" 
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_args
{
	int	num_philos;
	int	tm_die;
	int	tm_eat;
	int	tm_sleep;
	int	num_eats;
}	t_args;

typedef struct s_mutex
{
	pthread_mutex_t	text;
	pthread_mutex_t	death;
	pthread_mutex_t	fork[MAX_NUM_PHILOS + 2];
}	t_mutex;

typedef struct s_dinner
{
	int				end;
	int				satisfied_philos;
	long long int	tm_of_death;
	t_mutex			mutex;
	t_args			args;
	long long int	start_time;
}	t_dinner;

typedef struct s_philo
{
	int				index;
	long long int	last_meal;
	int				eaten_times;
	int				hand[2];
	t_dinner		*dinner;
}	t_philo;

int				check_arguments(int argc, char **argv);
int				init_simulation(t_dinner *dinner);
int				start_simulation(t_dinner *dinner, t_philo *philo);
void			*routine(void *philo_ptr);
void			*verify_end_conditions(void *philo_ptr);
void			take_forks(t_philo *philo);
void			drop_forks(t_philo *philo);
void			do_act(long long int time);
int				print_status(t_philo *philo, char *status);
int				ft_atoi(const char *nptr);
void			ft_bzero(void *s, size_t n);
long long int	get_current_time(void);
int				ft_strcmp(const char *s1, const char *s2);

#endif