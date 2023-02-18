/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ionorb <ionorb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:21:27 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/18 18:01:42 by ionorb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Parametros:	-Un size_t 'nmemb' (numero de miembros).
 * 		-Un size_t 'size' (tamano en bites de los valores miembros).
 *
 * Esta funcion crea a travez de malloc un arreglos de 'nmemb' espacios
 * donde cada espacio tiene un tamano de 'size' bits.
 *
 * Devuelve:	un puntero al arreglo creado. */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*p;

	if (size != 0 && nmemb * size / size != nmemb)
		return (NULL);
	p = (void *)ft_malloc(nmemb * size);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, nmemb * size);
	return ((void *)p);
}
