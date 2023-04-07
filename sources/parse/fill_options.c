/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 22:12:17 by yoel              #+#    #+#             */
/*   Updated: 2023/04/07 15:30:14 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_fill_check(char **line, t_option *option)
{
	if (ft_arg_count(line) != 3)
		ft_error("Wrong number of arguments for check", \
		CHECK_INSTRUCTIONS, NULL);
	option->check_color = ft_fill_rgb(line[1]);
	option->chess_ctrl = ft_fill_size(line[2], 0);
}

void	ft_fill_specular(char **line, t_option *option)
{
	if (ft_arg_count(line) != 3)
		ft_error("Wrong number of arguments for specular", \
		SPECULAR_INSTRUCTIONS, NULL);
	option->specular[0] = ft_fill_ratio(line[1]);
	option->specular[1] = ft_fill_size(line[2], 0);
}

void	ft_fill_mirror(char **line, t_option *option)
{
	if (ft_arg_count(line) != 2)
		ft_error("Wrong number of arguments for mirror", \
		MIRROR_INSTRUCTIONS, NULL);
	option->mirror = ft_fill_ratio(line[1]);
}

void	ft_fill_bumpmap(t_mrt *mrt, char **line, t_option *option)
{
	if (ft_arg_count(line) != 2)
		ft_error("Wrong number of arguments for bumpmap", \
		BUMP_INSTRUCTIONS, NULL);
	option->bump_map.path = ft_fill_xpm(line[1]);
	option->b_mp_ctrl = 1;
	option->bump_map.img = mlx_xpm_file_to_image(mrt->mlx, \
	option->bump_map.path, &option->bump_map.width, &option->bump_map.height);
	option->bump_map.addr = mlx_get_data_addr(option->bump_map.img, \
	&option->bump_map.bpp, &option->bump_map.sizel, &option->bump_map.endian);
	bump_to_array(&option->bump_map);
	mlx_destroy_image(mrt->mlx, option->bump_map.img);
	option->bump_map.addr = NULL;
	option->bump_map.img = NULL;
}

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

t_option	ft_fill_options(t_mrt *mrt, t_table *table, t_rgb color)
{
	t_option	option;

	option = \
	(t_option){0, get_opposite_color(color), 0, {0.3, 16}, 0, 0, \
	(t_bump){NULL, 0, 0, NULL, NULL, 0, 0, 0, NULL, 0.008}, \
	(t_bump){NULL, 0, 0, NULL, NULL, 0, 0, 0, NULL, 0.008}};
	while (table && table->next && eval_obj(table->next->line[0]) == OPTION)
	{
		if (eval_option(table->next->line[0]) == CHECK)
			ft_fill_check(table->next->line, &option);
		if (eval_option(table->next->line[0]) == SPECULAR)
			ft_fill_specular(table->next->line, &option);
		if (eval_option(table->next->line[0]) == MIRROR)
			ft_fill_mirror(table->next->line, &option);
		if (eval_option(table->next->line[0]) == BUMPMAP)
			ft_fill_bumpmap(mrt, table->next->line, &option);
		if (eval_option(table->next->line[0]) == TEXTURE)
			ft_fill_texture(mrt, table->next->line, &option);
		table = table->next;
	}
	return (option);
}
