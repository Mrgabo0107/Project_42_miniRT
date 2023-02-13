/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:20:31 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/13 22:32:55 by yridgway         ###   ########.fr       */
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

int	ft_check_line(char *line, int count[3])
{
	if (ft_obj_type(line) == AMBIENT)
		count[0]++;
	else if (ft_obj_type(line) == CAMERA)
		count[1]++;
	else if (ft_obj_type(line) == LIGHT)
		count[2]++;
	printf("line: %s\n", line);
	return (0);
}

int	ft_check_file(char *file)
{
	int		fd;
	int		count[3];
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_check_line(line, count))
			return (1);
		free(line);
	}
	if (line)
		free(line);
	// printf("count: %d %d %d\n", count[0], count[1], count[2]);
	return (0);
}
