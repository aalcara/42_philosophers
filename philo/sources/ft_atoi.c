/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcara- <aalcara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 23:07:22 by aalcara-          #+#    #+#             */
/*   Updated: 2021/09/24 23:07:36 by aalcara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	strsignal(const char *nptr, int *p)
{
	int		signal;

	signal = 1;
	if (*(nptr + *p) == '+')
	{
		*p = *p + 1;
	}
	else if (*(nptr + *p) == '-')
	{
		signal = -1;
		*p = *p + 1;
	}
	return (signal);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		nbr;
	int		sig;

	i = 0;
	nbr = 0;
	sig = 1;
	while ((*(nptr + i) == ' ') || (*(nptr + i) >= '\t' && *(nptr + i) <= '\r'))
	{
		i++;
	}
	sig = strsignal(nptr, &i);
	while (*(nptr + i) >= '0' && *(nptr + i) <= '9')
	{
		nbr = nbr * 10 + (*(nptr + i) - '0');
		i++;
	}
	return (nbr * sig);
}
