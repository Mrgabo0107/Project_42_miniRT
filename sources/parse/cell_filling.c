/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cell_filling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:52:58 by ionorb            #+#    #+#             */
/*   Updated: 2023/03/04 00:25:47 by ana              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_check_dots_and_minus(char *str)
{
	int	dot;
	int	minus;
	int	i;

	i = 0;
	dot = 0;
	minus = 0;
	while (str[i])
	{
		if (str[i] == '.')
			dot++;
		if (str[i] == '-')
			minus++;
		if (dot > 1)
			ft_error("Multiple dots(.) in value", str);
		if (minus > 1)
			ft_error("Multiple minuses(-) in value", str);
		if (i > 0 && str[i] == '-' && str[i - 1] != ' ')
			ft_error("Minus(-) in value", str);
		if (str[i] == '.' && !str[i + 1])
			ft_error("Dot(.) in value", str);
		i++;
	}
}

int	check_valid_number(char *str)
{
	int	i;
	int	count;
	int	minus;

	count = 0;
	i = 0;
	ft_check_dots_and_minus(str);
	while (str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		count++;
		i++;
		if (count > 10)
			return (ft_error(INT_RANGE, str), 0);
	}
	if (str[i++] == '.')
	{
		count = 0;
		while (str[i + count] >= '0' && str[i + count] <= '9' && count < 15)
			count++;
	}
	if (count >= 15)
		return (ft_error(DOUBLE_RANGE, str), 0);
	return (1);
}

void	valid_nums(char **line)
{
	while (line && *line)
		check_valid_number(*line++);
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
		ft_error("Invalid char in size value", cell);
	else if (check_for_chars("0123456789.", cell))
		ft_error("Invalid char in size value", cell);
	check_valid_number(cell);
	size = ft_atof(cell);
	if (fov && (size < 0 || size > 180))
		ft_error("Invalid size", cell);
	else if (size < 0 || size > 1000)
		ft_error("Invalid size", cell);
	return (size);
}

int	out_of_range(double num, double min, double max)
{
	if (num < min || num > max)
		return (1);
	return (0);
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
	valid_nums(line);
	pos.x = ft_atof(line[0]);
	pos.y = ft_atof(line[1]);
	pos.z = ft_atof(line[2]);
	if (dir == 0 && (out_of_range(pos.x, -1000, 1000) \
	|| out_of_range(pos.y, -1000, 1000) || out_of_range(pos.z, -1000, 1000)))
		ft_error(POS_RANGE, cell);
	if (dir == 1 && (out_of_range(pos.x, -1, 1) \
	|| out_of_range(pos.y, -1, 1) || out_of_range(pos.z, -1, 1)))
		ft_error(NORMAL_RANGE, cell);
	if (dir == 1 && pos.x == 0 && pos.y == 0 && pos.z == 0)
		ft_error("Normal must have at least one direction", cell);
	ft_free_array(line);
	return (pos);
}

t_rgb	ft_fill_rgb(char *cell)
{
	int		i;
	int		rgb[3];
	char	**line;

	line = ft_split(cell, ',');
	if (ft_arg_count(line) != 3 || check_for_chars("0123456789,", cell))
		ft_error("Invalid RGB value", cell);
	if (ft_strlen(line[0]) > 3 || ft_strlen(line[1]) > 3 || \
	ft_strlen(line[2]) > 3)
		ft_error("Invalid RGB value", cell);
	i = 0;
	while (i < 3)
	{
		rgb[i] = ft_atoi(line[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			ft_error("Invalid RGB value", cell);
		i++;
	}
	ft_free_array(line);
	return (ft_make_rgb(rgb[0], rgb[1], rgb[2]));
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
	check_valid_number(cell);
	if (!cell || !cell[0] || cell[0] == '.' || cell[i - 1] == '.'
		|| dotcount > 1 || ft_atof(cell) < 0.0 || ft_atof(cell) > 1.0)
		return (ft_error("Invalid ratio", cell), 1);
	return (ft_atof(cell));
}
