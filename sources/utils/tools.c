/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:22:52 by yridgway          #+#    #+#             */
/*   Updated: 2023/03/05 19:59:43 by ana              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*ft_chardup(char c)
{
	char	*tmp;

	tmp = ft_malloc(sizeof(char) * 2);
	tmp[0] = c;
	tmp[1] = '\0';
	return (tmp);
}

char	*ft_add_char(char *str, char c)
{
	char	*tmp;
	int		i;

	i = -1;
	if (!str)
		return (ft_chardup(c));
	tmp = ft_malloc(sizeof(char) * (ft_strlen(str) + 2));
	while (str && str[++i])
		tmp[i] = str[i];
	tmp[i] = c;
	tmp[i + 1] = '\0';
	return (ft_free(str), tmp);
}

int	ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (0);
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (1);
}

void	*ft_realloc(void *ptr, size_t size, size_t new_size)
{
	void	*new_ptr;

	new_ptr = ft_malloc(new_size);
	ft_memcpy(new_ptr, ptr, size);
	ft_free(ptr);
	return (new_ptr);
}

char	*get_next_line(int fd)
{
	char	line[10000];
	char	*copy;
	int		i;
	int		size;

	i = 0;
	size = 10000;
	i = 0;
	copy = line;
	while (read(fd, copy, 1) > 0)
	{
		if (*copy++ == '\n')
			break ;
		i++;
		if (i == size)
			ft_error("Line too long", \
			"Please keep lines under 10000 characters", NULL);
	}
	if (copy > line)
	{
		if (line[i] == '\n')
			line[i] = '\0';
		return (ft_strdup(line));
	}
	else
		return (NULL);
	return (NULL);
}
