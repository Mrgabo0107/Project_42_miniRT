/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ionorb <ionorb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:20:31 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/18 20:11:09 by ionorb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_obj_type(char *line)
{
	while (ft_isspace(*line))
		line++;
	if (*line == 'A')
		return (AMBIENT);
	else if (*line == 'c')
		return (CAMERA);
	else if (*line == 'l')
		return (LIGHT);
	else if (*line == 's' && *line + 1 == 'p')
		return (SPHERE);
	else if (*line == 'p' && *line + 1 == 'l')
		return (PLANE);
	else if (*line == 'c' && *line + 1 == 'y')
		return (CYLINDER);
	else
		return (0);
}

// int	ft_check_line(char *line, int count[3])
// {
// 	if (ft_obj_type(line) == AMBIENT)
// 		count[0]++;
// 	else if (ft_obj_type(line) == CAMERA)
// 		count[1]++;
// 	else if (ft_obj_type(line) == LIGHT)
// 		count[2]++;
// 	printf("%s", line);
// 	return (0);
// }

t_table	*ft_fill_table(char *file)
{
	int		fd;
	char	*line;
	t_table	*table;

	table = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (printf("Error opening %s\n", file), ft_quit(EXIT_ERROR), NULL);
	while (get_next_line(fd, &line) > 0)
	{
		if (line && line[0] && line[0] != '\n')
			table = ft_tableadd_new(table, ft_split_ws(line));
		else
			ft_free(line);
	}
	return (table);
}

int	ft_check_file(char *file)
{
	t_table	*table;
	int		i;

	table = ft_fill_table(file);
	while (table)
	{
		i = 0;
		while (i < 7)//table->line[i])
			printf("[%s] ", table->line[i++]);
		printf("\n");
		table = table->next;
	}
	return (0);
}
