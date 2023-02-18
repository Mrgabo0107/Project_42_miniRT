/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ionorb <ionorb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:22:52 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/18 19:01:12 by ionorb           ###   ########.fr       */
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

int	get_next_line(int fd, char **line)
{
	char	c;
	int		i;

	i = 0;
	*line = NULL;
	while (read(fd, &c, 1) > 0)
	{
		if (c)
			*line = ft_add_char(*line, c);
		if ((c == '\n') && i > 0)
			return (1);
		i++;
	}
	return (0);
}
