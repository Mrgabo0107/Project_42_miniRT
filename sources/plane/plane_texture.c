/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:32:21 by yridgway          #+#    #+#             */
/*   Updated: 2023/04/07 16:41:48 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	pl_txt_1(t_mrt *mrt, t_inter inter, t_vec new_inter)
{
	int		txt_coor[2];
	t_rgb	color;
	int		height;
	int		width;

	height = mrt->plane[inter.index].option.texture.height;
	width = mrt->plane[inter.index].option.texture.width;
	txt_coor[0] = (int)integer_part(new_inter.x / \
	mrt->plane[inter.index].option.texture.res_plan) % (height - 1);
	txt_coor[1] = (int)integer_part(new_inter.y / \
	mrt->plane[inter.index].option.texture.res_plan) % (width - 1);
	if (txt_coor[0] > height - 1)
		txt_coor[0] = height - 1;
	if (txt_coor[1] > width - 1)
		txt_coor[1] = width - 1;
	pthread_mutex_lock(mrt->mutexs);
	color = convert_to_rgb(mrt->plane[inter.index].option.texture.array \
	[txt_coor[0]][txt_coor[1]]);
	pthread_mutex_unlock(mrt->mutexs);
	return (color);
}

t_rgb	pl_txt_2(t_mrt *mrt, t_inter inter, t_vec new_inter)
{
	int		txt_coor[2];
	t_rgb	color;
	int		height;
	int		width;

	height = mrt->plane[inter.index].option.texture.height;
	width = mrt->plane[inter.index].option.texture.width;
	txt_coor[0] = height \
	- ((int)integer_part(v_abs(new_inter.x / \
	mrt->plane[inter.index].option.texture.res_plan)) % (height - 1));
	txt_coor[1] = (int)integer_part(new_inter.y / \
	mrt->plane[inter.index].option.texture.res_plan) % (width - 1);
	if (txt_coor[0] > height - 1)
		txt_coor[0] = height - 1;
	if (txt_coor[1] > width - 1)
		txt_coor[1] = width - 1;
	pthread_mutex_lock(mrt->mutexs);
	color = convert_to_rgb(mrt->plane[inter.index].option.texture.array \
	[txt_coor[0]][txt_coor[1]]);
	pthread_mutex_unlock(mrt->mutexs);
	return (color);
}

t_rgb	pl_txt_3(t_mrt *mrt, t_inter inter, t_vec new_inter)
{
	int		txt_coor[2];
	t_rgb	color;
	int		height;
	int		width;

	height = mrt->plane[inter.index].option.texture.height;
	width = mrt->plane[inter.index].option.texture.width;
	txt_coor[0] = (int)integer_part(new_inter.x / \
	mrt->plane[inter.index].option.texture.res_plan) % (height - 1);
	txt_coor[1] = width \
	- ((int)integer_part(v_abs(new_inter.y / \
	mrt->plane[inter.index].option.texture.res_plan)) % (width - 1));
	if (txt_coor[0] > height - 1)
		txt_coor[0] = height - 1;
	if (txt_coor[1] > width - 1)
		txt_coor[1] = width - 1;
	pthread_mutex_lock(mrt->mutexs);
	color = convert_to_rgb(mrt->plane[inter.index].option.texture.array \
	[txt_coor[0]][txt_coor[1]]);
	pthread_mutex_unlock(mrt->mutexs);
	return (color);
}

t_rgb	pl_txt_4(t_mrt *mrt, t_inter inter, t_vec new_inter)
{
	int		txt_coor[2];
	t_rgb	color;
	int		height;
	int		width;

	height = mrt->plane[inter.index].option.texture.height;
	width = mrt->plane[inter.index].option.texture.width;
	txt_coor[0] = height \
	- ((int)integer_part(v_abs(new_inter.x / \
	mrt->plane[inter.index].option.texture.res_plan)) % (height - 1));
	txt_coor[1] = width \
	- ((int)integer_part(v_abs(new_inter.y / \
	mrt->plane[inter.index].option.texture.res_plan)) % (width - 1));
	if (txt_coor[0] > height - 1)
		txt_coor[0] = height - 1;
	if (txt_coor[1] > width - 1)
		txt_coor[1] = width - 1;
	pthread_mutex_lock(mrt->mutexs);
	color = convert_to_rgb(mrt->plane[inter.index].option.texture.array \
	[txt_coor[0]][txt_coor[1]]);
	pthread_mutex_unlock(mrt->mutexs);
	return (color);
}

t_rgb	get_plane_texture(t_mrt *mrt, t_inter inter)
{
	t_mtrx	chg;
	t_vec	new_inter;
	t_rgb	color;

	if (!mrt->plane[inter.index].option.texture_ctrl)
		return (inter.color);
	chg = fill_mtrx(mrt->plane[inter.index].base.n1,
			mrt->plane[inter.index].base.n2,
			mrt->plane[inter.index].base.n3);
	new_inter = vec_rest(inter.inter_coor, mrt->plane[inter.index].pos);
	new_inter = mtrx_by_vec(chg, new_inter);
	if (new_inter.x >= 0 && new_inter.y >= 0)
		color = pl_txt_1(mrt, inter, new_inter);
	if (new_inter.x < 0 && new_inter.y >= 0)
		color = pl_txt_2(mrt, inter, new_inter);
	if (new_inter.x >= 0 && new_inter.y < 0)
		color = pl_txt_3(mrt, inter, new_inter);
	if (new_inter.x < 0 && new_inter.y < 0)
		color = pl_txt_4(mrt, inter, new_inter);
	return (color);
}
