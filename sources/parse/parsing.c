/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ionorb <ionorb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:20:31 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/19 00:41:03 by ionorb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

int	ft_count_objs(t_table *table)
{
	int	count[3];

	count[0] = 0;
	count[1] = 0;
	count[2] = 0;
	while (table)
	{
		if (eval_obj(table->line[0]) == AMBIENT)
			count[0]++;
		else if (eval_obj(table->line[0]) == CAMERA)
			count[1]++;
		else if (eval_obj(table->line[0]) == LIGHT)
			count[2]++;
		else if (eval_obj(table->line[0]) == -1)
			return (printf("Error\n"), ft_quit(INVALID_OBJECT, EXIT_ERROR), 1);
		table = table->next;
	}
	if (count[0] > 1 || count[1] > 1 || count[2] > 1)
		return (printf("Error\n"), ft_quit(TOO_MANY_CAPITALS, EXIT_ERROR), 1);
	if (count[0] == 0 || count[1] == 0 || count[2] == 0)
		return (printf("Error\n"), ft_quit(MISSING_CAPITALS, EXIT_ERROR), 1);
	return (0);
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

int	ft_parse(t_mrt *mrt, char *file)
{
	t_table	*table;
	int		i;

	(void)mrt;
	table = ft_fill_table(file);
	ft_count_objs(table);
	// ft_fill_objs(table);
	while (table)
	{
		i = 0;
		while (i < 7) //table->line[i])
			printf("[%s] ", table->line[i++]);
		printf("\n");
		table = table->next;
	}
	return (0);
}
