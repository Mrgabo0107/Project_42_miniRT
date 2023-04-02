/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cell_filling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel <yoel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:52:58 by ionorb            #+#    #+#             */
/*   Updated: 2023/04/02 19:54:58 by yoel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*ft_fill_xpm(char *cell)
{
	int		fd;

	fd = open(cell, O_RDONLY);
	if (fd < 0)
		ft_error("Invalid xpm file", cell, NULL);
	close(fd);
	return ((cell));
}

double	ft_fill_size(char *cell, int fov)
{
	double	size;

	if (fov && check_for_chars("0123456789", cell))
		ft_error("Invalid char in fov value", cell, FOV_INSTRUCTIONS);
	else if (check_for_chars("0123456789.", cell))
		ft_error("Invalid char in size value", cell, SIZE_INSTRUCTIONS);
	check_valid_number(cell);
	size = ft_atof(cell);
	if (fov && (size < 0 || size > 180))
		ft_error(FOV_RANGE, cell, FOV_INSTRUCTIONS);
	else if (size < 0 || size > 1000)
		ft_error(SIZE_RANGE, cell, SIZE_INSTRUCTIONS);
	return (size);
}

t_vec	ft_fill_pos(char *cell, int dir)
{
	t_vec	pos;
	char	**line;

	line = ft_split(cell, ',');
	if (ft_arg_count(line) != 3)
		ft_error("Wrong number of values in pos", cell, POS_INSTRUCTIONS);
	if (check_for_chars("0123456789,-.", cell))
		ft_error("Invalid char in pos", cell, POS_INSTRUCTIONS);
	valid_nums(line);
	pos.x = ft_atof(line[0]);
	pos.y = ft_atof(line[1]);
	pos.z = ft_atof(line[2]);
	if (dir == 0 && (out_of_range(pos.x, -1000, 1000) \
	|| out_of_range(pos.y, -1000, 1000) || out_of_range(pos.z, -1000, 1000)))
		ft_error(POS_RANGE, cell, POS_INSTRUCTIONS);
	if (dir == 1 && (out_of_range(pos.x, -1, 1) \
	|| out_of_range(pos.y, -1, 1) || out_of_range(pos.z, -1, 1)))
		ft_error(NORMAL_RANGE, cell, NORMAL_INSTRUCTIONS);
	if (dir == 1 && pos.x == 0 && pos.y == 0 && pos.z == 0)
		ft_error("Normal must have at least one direction", cell, \
		NORMAL_INSTRUCTIONS);
	ft_free_array(line);
	return (pos);
}

t_rgb	ft_fill_rgb(char *cell)
{
	int		i;
	int		rgb[3];
	char	**line;

	line = ft_split(cell, ',');
	if (ft_arg_count(line) != 3)
		ft_error("Wrong number of values in rgb", cell, RGB_INSTRUCTIONS);
	if (check_for_chars("0123456789,", cell))
		ft_error("Invalid char in rgb", cell, RGB_INSTRUCTIONS);
	i = 0;
	while (i < 3)
	{
		rgb[i] = ft_atoi(line[i]);
		if (rgb[i] < 0 || rgb[i] > 255 || ft_strlen(line[0]) > 3 \
		|| ft_strlen(line[1]) > 3 || ft_strlen(line[2]) > 3)
			ft_error(RGB_RANGE, cell, RGB_INSTRUCTIONS);
		i++;
	}
	ft_free_array(line);
	return (ft_make_rgb(rgb[0], rgb[1], rgb[2]));
}

double	ft_fill_ratio(char *cell)
{
	if (check_for_chars("0123456789.", cell))
		ft_error("Invalid char in ratio", cell, RATIO_INSTRUCTIONS);
	check_valid_number(cell);
	if (ft_atof(cell) < 0.0 || ft_atof(cell) > 1.0)
		ft_error(cell, RATIO_INSTRUCTIONS, NULL);
	return (ft_atof(cell));
}
