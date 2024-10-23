/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 22:53:47 by yridgway          #+#    #+#             */
/*   Updated: 2023/04/08 13:28:45 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_write_to_file(char *line, int fd)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

char	*ft_write_pos(t_vec pos)
{
	char	*line;

	line = ft_strjoin_free(ft_ftoa(pos.x), (","));
	line = ft_strjoin_free(line, ft_ftoa(pos.y));
	line = ft_strjoin_free(line, (","));
	line = ft_strjoin_free(line, ft_ftoa(pos.z));
	return (line);
}

t_vec	ft_unnormalize(t_vec vec)
{
	double	max;

	max = v_abs(vec.x);
	if (v_abs(vec.y) > max)
		max = v_abs(vec.y);
	if (v_abs(vec.z) > max)
		max = v_abs(vec.z);
	vec.x *= 1 / max;
	vec.y *= 1 / max;
	vec.z *= 1 / max;
	return (vec);
}

char	*ft_write_dir(t_vec dir)
{
	char	*line;

	dir = ft_unnormalize(dir);
	line = ft_strjoin_free(ft_ftoa(dir.x), (","));
	line = ft_strjoin_free(line, ft_ftoa(dir.y));
	line = ft_strjoin_free(line, (","));
	line = ft_strjoin_free(line, ft_ftoa(dir.z));
	return (line);
}

char	*ft_write_rgb(t_rgb color)
{
	char	*line;

	line = ft_strjoin_free(ft_itoa(color.r), (","));
	line = ft_strjoin_free(line, ft_itoa(color.g));
	line = ft_strjoin_free(line, (","));
	line = ft_strjoin_free(line, ft_itoa(color.b));
	return (line);
}
