/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoli.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:14:11 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/15 18:18:46 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Parametros:	Una cadena de carecteres 'nptr'.
 *
 * Esta funcion transforma en int la cadena de caracteres punteada por 'nptr' 
 * leyendola de izquierda a derecha dejando pasar whitespces evaluando si 
 * despus de estos hay un '-' que defina si como negativo el retorno.
 *
 * Devuelve: el entero que este despues de los posibles whitespaces y caracter
 * '-'. */

#include "libft.h"

long int	ft_atoli(const char *nptr)
{
	long int	i;
	long int	j;
	long int	k;

	i = 0;
	j = 0;
	k = 0;
	while ((9 <= nptr[i] && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
	{
		k = 1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		j += nptr[i] - 48;
		j *= 10;
		i++;
	}
	if (k == 1)
		j *= -1;
	return (j / 10);
}
