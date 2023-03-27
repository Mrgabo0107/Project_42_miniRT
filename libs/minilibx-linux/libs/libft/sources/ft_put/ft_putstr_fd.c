/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 21:36:07 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/15 18:18:46 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Parametros:	-Un puntero a una cadena e caracteres 's'.
 * 		-Un 'file descriptor' tipo int 'fd', que caracteriza a un
 * 		 archivo.
 *
 * Esta funcion escribe el string 's' sobre el archivo definido por el "file
 * descriptor" 'fd'.
 *
 * Devuelve:	n/a es tipo void. */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
