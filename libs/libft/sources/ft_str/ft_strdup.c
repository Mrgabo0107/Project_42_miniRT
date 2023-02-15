/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:26:52 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/15 18:18:46 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Parametros:	-Un puntero a una cadena de caracteres 's'.
 *
 * Esta funcion crea con malloc un arreglo con la longitud de la cadena 's'
 * y hace una copia de 's' dentro de este arreglo.
 *
 * Devuelve: La copia de 's' creada. */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*cpy;
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	cpy = (char *)ft_malloc(NULL, len + 1);
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
