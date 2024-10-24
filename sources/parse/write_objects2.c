/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 22:54:42 by yridgway          #+#    #+#             */
/*   Updated: 2023/04/08 13:31:36 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_write_cones(t_cone *cone, int count, int fd)
{
	int		i;
	char	*line;

	i = 0;
	while (i < count)
	{
		ft_write_to_file(ft_strjoin_free(("#"), ft_itoa(i + 1)), fd);
		line = ft_strjoin_free(("co\t\t"), ft_write_pos(cone[i].pos));
		line = ft_strjoin_free(line, ("\t\t"));
		line = ft_strjoin_free(line, ft_write_dir(cone[i].dir));
		line = ft_strjoin_free(line, ("\t\t"));
		line = ft_strjoin_free(line, ft_ftoa(rad_and_deg(cone[i].angle, 0)));
		line = ft_strjoin_free(line, ("\t\t"));
		// printf("\ncone %f, %s\n", cone[i].height, ft_ftoa(cone[i].height));
		line = ft_strjoin_free(line, ft_ftoa(cone[i].height));
		line = ft_strjoin_free(line, ("\t\t"));
		line = ft_strjoin_free(line, ft_write_rgb(cone[i].color));
		ft_write_to_file(line, fd);
		ft_write_options(cone[i].option, fd);
		ft_free(line);
		ft_write_to_file("", fd);
		i++;
	}
}
