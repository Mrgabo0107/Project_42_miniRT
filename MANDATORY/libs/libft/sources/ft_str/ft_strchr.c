/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:26:13 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/15 18:18:46 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Parametros	- Un puntero a una cadena de caracteres 's'.
 * 		- un caracter 'c' visto omo entero.
 * Esta funcion busca la primera ocurrencia del caracter 'c' en la cadena 's'
 * evaluande de izquierda a derecha.
 *
 * Devuelve: un puntero char en la posicion de esa ocurrencia. */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}
