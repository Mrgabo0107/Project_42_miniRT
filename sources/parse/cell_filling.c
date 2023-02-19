/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cell_filling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:52:58 by ionorb            #+#    #+#             */
/*   Updated: 2023/02/19 17:54:50 by yridgway         ###   ########.fr       */
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
