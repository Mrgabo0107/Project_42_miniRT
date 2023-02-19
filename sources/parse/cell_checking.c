/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cell_checking.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:52:58 by ionorb            #+#    #+#             */
/*   Updated: 2023/02/19 18:26:32 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

u_int	ft_fill_rgb(char *cell)
{
	int	i;
	int	rgb[3];
	int	count;

	i = 0;
	count = 0;
	rgb[count++] = ft_atoi(cell);
	if (rgb[count - 1] < 0 || rgb[count - 1] > 255)
		return (ft_error("Invalid RGB value", cell), 1);
	while (cell && cell[i])
	{
		if (!ft_strchr("0123456789,", cell[i]))
			return (ft_error("Invalid RGB value", cell), 1);
		if (ft_strchr(",", cell[i]))
		{
			if (count > 2)
				return (ft_error("Invalid RGB value", cell), 1);
			rgb[count++] = ft_atoi(cell + i);
			if (rgb[count - 1] < 0 || rgb[count - 1] > 255)
				return (ft_error("Invalid RGB value", cell), 1);
		}
		i++;
	}
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

int	ft_check_ratio(char *cell)
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
	return (0);
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
