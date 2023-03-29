/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ionorb <ionorb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:54:13 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/18 18:01:42 by ionorb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Parametros:	Un entero 'c'.
 *
 * Esta funcion toma el entero y lo transforma en una cadena de caracteres.
 *
 * Devuelve:	 La cadena de caracteres con el entero representado en char. */

#include "libft.h"

static int	num_caract(int n)
{
	int			cont;
	long int	cpy;
	long int	tenpow;

	cpy = (long int)n;
	cont = 1;
	tenpow = 1;
	if (cpy < 0)
	{
		cont++;
		cpy *= -1;
	}
	while (cpy / (10 * tenpow) > 0)
	{
		cont++;
		tenpow *= 10;
	}
	return (cont);
}

static long int	potencia(int c)
{
	long int	ret;
	int			i;

	ret = 1;
	i = 0;
	while (i < c)
	{
		ret *= 10;
		i++;
	}
	return (ret / 10);
}

static void	writer(char *str, int n)
{
	int			i;
	long int	cpy;
	long int	power;

	cpy = (long int)n;
	i = 0;
	if (cpy < 0)
	{
		str[i] = '-';
		i++;
		cpy *= -1;
	}
	power = potencia(num_caract(cpy));
	while (power > 0)
	{
		str[i] = (cpy / power) + 48;
		cpy = (cpy - (cpy / power) * power);
		power /= 10;
		i++;
	}
	str[i] = '\0';
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = num_caract(n) + 1;
	str = (char *)ft_malloc(sizeof(char) * (len));
	if (!str)
		return (NULL);
	writer(str, n);
	return (str);
}
