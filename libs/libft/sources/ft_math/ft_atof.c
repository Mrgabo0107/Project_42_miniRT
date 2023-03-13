/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:31:14 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/15 18:18:46 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Parametros:  -Una cadena de caracteres aue representa un double.
 *
 * Esta funcion lee la cadena y la aalmacena en un double.
 *
 * Devuelve: el double que representa la cadena */

#include "libft.h"

static double	ft_power(int base, unsigned int power)
{
	int	result;
	int	i;

	result = 1;
	i = 0;
	while (i < power)
	{
		result = result * base;
		i++;
	}
	return (result);
}

static double	ft_atof_decimal(char *str)
{
	double	nb;
	int		power;

	nb = 0;
	power = 0;
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			nb = (nb * 10) + (*str - '0');
			str++;
			power++;
		}
		if (nb < 0)
			nb = -nb;
	}
	nb = nb / ft_power(10, power);
	return (nb);
}

double	ft_atof(char *s)
{
	double	nb;
	int		sign;

	nb = 0;
	sign = 1;
	while (*s == ' ' || (*s >= '\t' && *s <= '\r'))
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		nb = (nb * 10) + ((*s++) - '0');
	}
	nb = nb + ft_atof_decimal(s);
	return (nb * sign);
}
