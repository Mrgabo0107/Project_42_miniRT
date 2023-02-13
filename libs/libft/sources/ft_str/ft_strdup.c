/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:26:52 by gamoreno          #+#    #+#             */
/*   Updated: 2022/06/15 17:31:48 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Parametros:	-Un puntero a una cadena de caracteres 's'.
 *
 * Esta funcion crea con malloc un arreglo con la longitud de la cadena 's'
 * y hace una copia de 's' dentro de este arreglo.
 *
 * Devuelve: La copia de 's' creada. */

#include "../../includes/libft.h"

char	*ft_strdup(const char *s)
{
	char	*cpy;
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	cpy = (char *)malloc(len + 1);
	if (!cpy)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		*(cpy + i) = *(s + i);
		i++;
	}
	return (cpy);
}
