/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:42:35 by gamoreno          #+#    #+#             */
/*   Updated: 2022/08/17 04:30:09 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Parametros: Puntero a una cadena de caracteres
 *
 * Esta funcion cuenta el numero de caracteres de un string desde el puntero al
 * primer caracter hasta el caracter '\0'.
 *
 * Devuelve: un size_t con el numero de caracteres */

#include "../../includes/libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
