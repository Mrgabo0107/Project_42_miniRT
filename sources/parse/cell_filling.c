/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cell_filling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:52:58 by ionorb            #+#    #+#             */
/*   Updated: 2023/02/27 17:51:11 by ana              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_valid_number(char *str)
{
	int	i;
	int	dot;
	int	minus;

	minus = 0;
	dot = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '.')
			dot++;
		if (str[i] == '-')
			minus++;
		i++;
	}
	if (dot > 1 || minus > 1 || i > 11)
		return (0);
	return (1);
}

int	valid_nums(char **line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!is_valid_number(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_for_chars(char *str, char *cell)
{
	int	i;

	i = 0;
	while (cell && cell[i])
	{
		if ((cell[i] == '.' && cell[i + 1] == '-') || \
		(cell[i] == '-' && cell[i + 1] == ',') || \
		(cell[i] == '-' && cell[i + 1] == '.') || \
		(cell[i] == ',' && cell[i + 1] == '.') || \
		(cell[i] == '.' && cell[i + 1] == ','))
			return (1);
		if (!ft_strchr(str, cell[i]))
			return (1);
		i++;
	}
	if (!cell || !cell[0] || cell[0] == ',' || cell[i - 1] == ',' \
	|| cell[0] == '.' || cell[i - 1] == '.')
		return (1);
	return (0);
}

double	ft_fill_size(char *cell, int fov)
{
	double	size;

	if (fov && check_for_chars("0123456789", cell))
		ft_error("Invalid size", cell);
	else if (check_for_chars("0123456789.", cell))
		ft_error("Invalid size", cell);
	if (!is_valid_number(cell))
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
	if (ft_arg_count(line) != 3 || check_for_chars("0123456789,-.", cell))
		ft_error("Invalid position", cell);
	if (!valid_nums(line))
		ft_error("Invalid position", cell);
	pos.x = ft_atof(line[0]);
	pos.y = ft_atof(line[1]);
	pos.z = ft_atof(line[2]);
	if (dir == 1)
	{
		if (pos.x < -1 || pos.x > 1 || pos.y < -1 || pos.y > 1 || \
		pos.z < -1 || pos.z > 1)
			ft_error("Invalid position", cell);
		if (pos.x == 0 && pos.y == 0 && pos.z == 0)
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

	line = ft_split(cell, ',');
	if (ft_arg_count(line) != 3 || check_for_chars("0123456789,", cell))
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
	if (!cell || !cell[0] || cell[0] == '.' || cell[i - 1] == '.'
		|| dotcount > 1 || !is_valid_number(cell)
		|| ft_atof(cell) < 0.0 || ft_atof(cell) > 1.0)
		return (ft_error("Invalid ratio", cell), 1);
	return (ft_atof(cell));
}
