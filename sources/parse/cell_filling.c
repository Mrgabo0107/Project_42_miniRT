/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cell_filling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:52:58 by ionorb            #+#    #+#             */
/*   Updated: 2023/02/19 23:48:48 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_for_chars(char *str, char *cell)
{
	int	i;

	i = 0;
	while (cell && cell[i])
	{
		if ((cell[i] == '-' && cell[i + 1] == '-') || \
		(cell[i] == ',' && cell[i + 1] == ',') || \
		(cell[i] == '.' && cell[i + 1] == '.') || \
		(cell[i] == '-' && cell[i + 1] == ',') || \
		(cell[i] == '-' && cell[i + 1] == '.') || \
		(cell[i] == ',' && cell[i + 1] == '.') || \
		(cell[i] == '.' && cell[i + 1] == ','))
			return (1);
		if (!ft_strchr(str, cell[i]))
			return (1);
		i++;
	}
	if (!cell || !cell[0] || cell[0] == ',' || cell[i - 1] == ',')
		return (ft_error("Invalid RGB value", cell), 1);
	return (0);
}

double	ft_fill_size(char *cell, int fov)
{
	double	size;

	if (fov && check_for_chars("0123456789", cell))
		ft_error("Invalid size", cell);
	else if (check_for_chars("0123456789.", cell))
		ft_error("Invalid size", cell);
	size = ft_atof(cell);
	if (fov && (size < 0 || size > 180))
		ft_error("Invalid size", cell);
	else if (size < 0 || size > 1000)
		ft_error("Invalid size", cell);
	return (size);
}

t_vec	ft_fill_pos(char *cell, int dir)
{
	t_vec	pos;
	char	**line;

	line = ft_split(cell, ',');
	if (ft_arg_count(line) != 3)
		ft_error("Invalid position", cell);
	if (check_for_chars("0123456789,-.", cell))
		ft_error("Invalid position", cell);
	pos.x = ft_atof(line[0]);
	pos.y = ft_atof(line[1]);
	pos.z = ft_atof(line[2]);
	if (dir == 1)
	{
		if (pos.x < -1 || pos.x > 1 || pos.y < -1 || pos.y > 1 || \
		pos.z < -1 || pos.z > 1)
			ft_error("Invalid position", cell);
	}
	ft_free_array(line);
	return (pos);
}

uint	ft_fill_rgb(char *cell)
{
	int		i;
	int		rgb[3];
	char	**line;

	if (check_for_chars("0123456789,", cell))
		return (ft_error("Invalid RGB value", cell), 1);
	line = ft_split(cell, ',');
	if (ft_arg_count(line) != 3)
		return (ft_error("Invalid RGB value", cell), 1);
	if (ft_strlen(line[0]) > 3 || ft_strlen(line[1]) > 3 || \
	ft_strlen(line[2]) > 3)
		return (ft_error("Invalid RGB value", cell), 1);
	i = 0;
	while (i < 3)
	{
		rgb[i] = ft_atoi(line[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (ft_error("Invalid RGB value", cell), 1);
		i++;
	}
	ft_free_array(line);
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

double	ft_fill_ratio(char *cell)
{
	int	i;
	int	dotcount;

	i = 0;
	dotcount = 0;
	while (cell && cell[i])
	{
		if (!ft_strchr("0123456789.", cell[i]))
			return (ft_error("Invalid ratio", cell), 1);
		if (ft_strchr(".", cell[i]))
			dotcount++;
		i++;
	}
	if (!cell || !cell[0] || cell[0] == '.' || cell[i - 1] == '.' || \
	dotcount > 1 || ft_atof(cell) < 0.0 || ft_atof(cell) > 1.0)
		return (ft_error("Invalid ratio", cell), 1);
	return (ft_atof(cell));
}

// int	ft_check_chars(char **line, char *chars)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (line && line[i])
// 	{
// 		j = 0;
// 		while (line[i][j])
// 		{
// 			if (!ft_strchr(chars, line[i][j]))
// 				return (ft_error("Invalid char", &line[i][j]), 1);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }
