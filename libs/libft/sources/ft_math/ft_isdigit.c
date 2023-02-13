/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:39:36 by gamoreno          #+#    #+#             */
/*   Updated: 2022/06/30 14:39:40 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Parametros: caracter visto como entero.
 *
 * Esta funcion evalua si el caracter pasado como parametro es un digito
 *
 * Devuelve: 1 si es digito o 0 en el caso contario. */

#include "../../includes/libft.h"

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}
