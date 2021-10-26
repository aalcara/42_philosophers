/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalcara- <aalcara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 23:07:22 by aalcara-          #+#    #+#             */
/*   Updated: 2021/10/23 00:24:14 by aalcara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	int		nbr;

	i = 0;
	nbr = 0;
	while ((*(nptr + i) == ' ') || (*(nptr + i) >= '\t' && *(nptr + i) <= '\r'))
	{
		i++;
	}
	while (*(nptr + i) >= '0' && *(nptr + i) <= '9')
	{
		nbr = nbr * 10 + (*(nptr + i) - '0');
		i++;
	}
	return (nbr);
}
