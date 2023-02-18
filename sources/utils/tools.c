/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ionorb <ionorb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:22:52 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/18 18:01:42 by ionorb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*ft_add_char(char *str, char c)
{
	char	*tmp;
	int		i;

	i = -1;
	if (!str)
		return (ft_strdup(&c));
	tmp = ft_malloc(sizeof(char) * (ft_strlen(str) + 2));
	while (str[++i])
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
		if ((c == '\n' || !c) && i > 0)
			return (1);
		*line = ft_add_char(*line, c);
		i++;
	}
	return (0);
}
