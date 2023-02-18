/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ionorb <ionorb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 21:02:11 by ionorb            #+#    #+#             */
/*   Updated: 2023/02/19 00:45:59 by ionorb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_strcmp_1(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

int	eval_obj(char *line)
{
	if (ft_strcmp_1(line, "sp") == 0)
		return (SPHERE);
	if (ft_strcmp_1(line, "pl") == 0)
		return (PLANE);
	if (ft_strcmp_1(line, "cy") == 0)
		return (CYLINDER);
	if (ft_strcmp_1(line, "L") == 0)
		return (LIGHT);
	if (ft_strcmp_1(line, "A") == 0)
		return (AMBIENT);
	if (ft_strcmp_1(line, "C") == 0)
		return (CAMERA);
	return (-1);
}


t_table	*ft_fill_table(char *file)
{
	int		fd;
	char	*line;
	t_table	*table;

	table = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (printf("Error\n"), ft_quit(FILE_ERROR, EXIT_ERROR), NULL);
	while (get_next_line(fd, &line) > 0)
	{
		if (line && line[0] && line[0] != '\n')
			table = ft_tableadd_new(table, ft_split_ws(line));
		else
			ft_free(line);
	}
	return (table);
}
