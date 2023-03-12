/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:18:07 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/05 21:13:50 by ana              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Parametros: Un puntero void 's' y un size_t 'n'.
 *
 * Esta funcion toma el puntero 's' y a partir de ese escribe el carcer nulo 
 * 'n' veces.
 *
 * Devuelve: nada. */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}
