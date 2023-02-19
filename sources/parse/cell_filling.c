/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cell_filling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:52:58 by ionorb            #+#    #+#             */
/*   Updated: 2023/02/19 20:28:20 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// int	ft_check_rgb(char *line[7])
// {
// 	int	i;

// 	i = 1;
// 	while (line[i])
// 	{
// 		if (ft_atoi(line[i]) < 0 || ft_atoi(line[i]) > 255)
// 			return (ft_error("Invalid RGB value", line[i]), 1);
// 		i++;
// 	}
// 	return (0);
// }

// int	ft_check_xyz(char *line[7])
// {
// 	int	i;

// 	i = 1;
// 	while (line[i])
// 	{
// 		if (ft_atoi(line[i]) < -1000 || ft_atoi(line[i]) > 1000)
// 			return (ft_error("Invalid XYZ value", line[i]), 1);
// 		i++;
// 	}
// 	return (0);
// }

// int	ft_check_size(char *line[7])
// {
// 	int	i;

// 	i = 1;
// 	while (line[i])
// 	{
// 		if (ft_atoi(line[i]) < 0 || ft_atoi(line[i]) > 1000)
// 			return (ft_error("Invalid size", line[i]), 1);
// 		i++;
// 	}
// 	return (0);
// }

// int	ft_check_normal(char *line[7])
// {
// 	int	i;

// 	i = 1;
// 	while (line[i])
// 	{
// 		if (ft_atoi(line[i]) < -1 || ft_atoi(line[i]) > 1)
// 			return (ft_error("Invalid normal", line[i]), 1);
// 		i++;
// 	}
// 	return (0);
// }

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

t_vec	ft_fill_pos(char *cell)
{
	t_vec	pos;
	char	**line;

	// pos = malloc(sizeof(t_vec));
	line = ft_split(cell, ',');
	if (ft_arg_count(line) != 3)
		ft_error("Invalid position", cell);
	if (check_for_chars("0123456789,-.", cell))
		ft_error("Invalid position", cell);
	pos.x = ft_atof(line[0]);
	pos.y = ft_atof(line[1]);
	pos.z = ft_atof(line[2]);
	ft_free_array(line);
	return (pos);
}

t_vec	ft_fill_dir(char *cell)
{
	t_vec	dir;
	char	**line;
	double	xyz[3];
	int		i;

	i = 0;
	// dir = malloc(sizeof(t_vec));
	line = ft_split(cell, ',');
	if (ft_arg_count(line) != 3)
		ft_error("Invalid direction", cell);
	if (check_for_chars("0123456789,-.", cell))
		ft_error("Invalid direction", cell);
	while (i < 3)
	{
		xyz[i] = ft_atof(line[i]);
		if (xyz[i] < -1 || xyz[i] > 1)
			ft_error("Invalid direction", cell);
		i++;
	}
	dir.x = xyz[0];
	dir.y = xyz[1];
	dir.z = xyz[2];
	ft_free_array(line);
	return (dir);
}

double	ft_fill_fov(char *cell)
{
	double	fov;

	if (check_for_chars("0123456789", cell))
		return (ft_error("Invalid FOV value", cell), 1);
	if (ft_strlen(cell) > 3)
		return (ft_error("Invalid FOV value", cell), 1);
	fov = ft_atoi(cell);
	if (fov < 0 || fov > 180)
		return (ft_error("Invalid FOV value", cell), 1);
	return (fov);
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

int	ft_check_chars(char **line, char *chars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line && line[i])
	{
		j = 0;
		while (line[i][j])
		{
			if (!ft_strchr(chars, line[i][j]))
				return (ft_error("Invalid char", &line[i][j]), 1);
			j++;
		}
		i++;
	}
	return (0);
}
