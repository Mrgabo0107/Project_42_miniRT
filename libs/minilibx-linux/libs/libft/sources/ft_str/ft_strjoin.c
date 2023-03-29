/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ionorb <ionorb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:45:10 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/18 18:01:42 by ionorb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Parametros:	-Dos cadenas de caacteres 's1' y 's2' respectivamente.
*
 * Esta funcion crea con malloc un arreglo suficientemente grande para contener
 * 's1' y 's2' concatenadas mas el caracter '\0'.
 *
 * Devuelve:	El arreglo creado como la cadena de caracteres resultante de la
 * 		concatenacion e 's1' y 's2' terminada en el caracter nulo. */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	char	*str;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)ft_malloc(sizeof(char) * len);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[i - ft_strlen(s1)])
	{
		str[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	str[i] = '\0';
	return (str);
}
