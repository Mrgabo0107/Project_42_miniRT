/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_options2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 22:12:17 by yoel              #+#    #+#             */
/*   Updated: 2023/04/07 17:52:16 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_fill_texture(t_mrt *mrt, char **line, t_option *option)
{
	if (ft_arg_count(line) != 2)
		ft_error("Wrong number of arguments for texture", \
		TEXTURE_INSTRUCTIONS, NULL);
	option->texture.path = ft_fill_xpm(line[1]);
	option->texture_ctrl = 1;
	option->texture.img = mlx_xpm_file_to_image(mrt->mlx, \
	option->texture.path, &option->texture.width, &option->texture.height);
	option->texture.addr = mlx_get_data_addr(option->texture.img, \
	&option->texture.bpp, &option->texture.sizel, &option->texture.endian);
	bump_to_array(&option->texture);
	mlx_destroy_image(mrt->mlx, option->texture.img);
	option->texture.addr = NULL;
	option->texture.img = NULL;
}
