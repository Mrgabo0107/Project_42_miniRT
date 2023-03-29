/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:05:32 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/27 21:45:21 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Parametros:	-Un puntero 's' a una cadena de caracteres.
 * 		-Un char 'c'.
 *
 * Esta funcion crea subcadenas de caracteres de la cadena 's' correspondientes 
 * a lo que esta entre cada ocurrencia del caracter 'c'.
 *
 * Devuelve:	Un puntero a un arreglo que contiene las subcadenas creadas. */

#include "libft.h"

static long unsigned int	contador(char const *str, char c)
{
	size_t	i;
	size_t	cont;

	i = 0;
	cont = 0;
	while (str && str[i])
	{
		if (str[i] != c && (i == 0 || (i > 0 && str[i - 1] == c)))
		{
			cont++;
			i++;
		}
		else
			i++;
	}
	return (cont);
}

static char	*mkline(char const *str, char c)
{
	size_t		i;
	size_t		j;
	char		*line;

	i = 0;
	j = 0;
	while (str[i] != c && i < ft_strlen(str))
		i++;
	line = (char *)ft_malloc(sizeof(char) * (1 + i));
	if (!line)
		return (NULL);
	while (j < i)
	{
		line[j] = str[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	**free_all(char **s)
{
	long unsigned int	i;

	i = 0;
	while (s[i])
		ft_free(s[i++]);
	ft_free(s);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char		**tab;
	size_t		i;
	size_t		j;

	tab = (char **)ft_malloc(sizeof(char *) * (contador(s, c) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_strlen(s))
	{
		while (s[i] == c && s[i + 1] == c && s[i + 1])
			i++;
		if (s[i] != c)
		{
			tab[j] = mkline(s + i, c);
			if (tab[j] == NULL)
				return (free_all(tab));
			i += ft_strlen(tab[j]);
			j++;
		}
		i++;
	}
	tab[j] = NULL;
	return (tab);
}
