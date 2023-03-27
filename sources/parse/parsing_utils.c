/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 21:02:11 by ionorb            #+#    #+#             */
/*   Updated: 2023/03/27 21:54:51 by yridgway         ###   ########.fr       */
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

int	eval_option(char *line)
{
	if (ft_strcmp_1(line, "mir") == 0)
		return (MIRROR);
	if (ft_strcmp_1(line, "check") == 0)
		return (CHECK);
	if (ft_strcmp_1(line, "trans") == 0)
		return (TRANSPARENT);
	if (ft_strcmp_1(line, "spec") == 0)
		return (SPECULAR);
	if (ft_strcmp_1(line, "bump") == 0)
		return (BUMPMAP);
	return (-1);
}

int	eval_obj(char *line)
{
	if (ft_strcmp_1(line, "sp") == 0)
		return (SPHERE);
	if (ft_strcmp_1(line, "pl") == 0)
		return (PLANE);
	if (ft_strcmp_1(line, "cy") == 0)
		return (CYLINDER);
	if (ft_strcmp_1(line, "co") == 0)
		return (CONE);
	if (ft_strcmp_1(line, "L") == 0)
		return (LIGHT);
	if (ft_strcmp_1(line, "A") == 0)
		return (AMBIENT);
	if (ft_strcmp_1(line, "C") == 0)
		return (CAMERA);
	if (eval_option(line) != -1)
		return (OPTION);
	return (-1);
}

int	ft_arg_count(char **line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

t_table	*ft_fill_table(int fd, int num_objs)
{
	char	*line;
	t_table	*table;

	table = NULL;
	line = ft_strdup("#");
	while (line)
	{
		if (line && line[0] && line[0] != '\n' && line[0] != '#')
			table = ft_tableadd_new(table, ft_split_ws(line), num_objs);
		else
			ft_free(line);
		line = get_next_line(fd);
	}
	return (table);
}

int	*int_arrcpy(int *arr, int size)
{
	int	*new;
	int	i;

	i = 0;
	new = ft_malloc(sizeof(int) * size);
	while (i < size)
	{
		new[i] = arr[i];
		i++;
	}
	return (new);
}

void	ft_error(char *msg, char *extra, char *extra2)
{
	printf("Error\n");
	if (msg && extra && extra2)
		printf("%s: %s: %s\n", msg, extra, extra2);
	else if (msg && extra)
		printf("%s: %s\n", msg, extra);
	else if (msg)
		printf("%s\n", msg);
	ft_quit(EXIT_ERROR);
}
