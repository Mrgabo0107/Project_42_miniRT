/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:25:02 by gamoreno          #+#    #+#             */
/*   Updated: 2023/04/08 12:52:40 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_curr_ob	define_curr_obj(int type, int index)
{
	t_curr_ob	curr_obj;

	curr_obj.index = index;
	curr_obj.type = type;
	return (curr_obj);
}

void	light_ctr(t_mrt *mrt, int key)
{
	if (mrt->curr_obj.type == LIGHT)
	{
		if (key == PLUS && mrt->light[mrt->curr_obj.index].ratio < 0.9)
			mrt->light[mrt->curr_obj.index].ratio += 0.1;
		if (key == MINUS && mrt->light[mrt->curr_obj.index].ratio > 0.1)
			mrt->light[mrt->curr_obj.index].ratio -= 0.1;
	}
	if (key == L)
		mrt->curr_obj = define_curr_obj(LIGHT, \
		(mrt->curr_obj.index + 1) % mrt->obj_count[LIGHT]);
}

void	object_ctr(t_mrt *mrt, int key)
{
	if (mrt->curr_obj.type != CAMERA)
	{
		move_obj(mrt, key);
		rotate_obj(mrt, key);
		chg_options(mrt, key);
		chess_ctr(mrt, key);
		radius_ctr(mrt, key);
		height_ctr(mrt, key);
		fov_ctr(mrt, key);
		bump_option(mrt, key);
		texture_option(mrt, key);
	}
}

int	key_press(int key, t_mrt *mrt)
{
	if (key == Z)
		return (save_scene(mrt), 0);
	if (key == X)
		return (write_to_ppm(mrt), 0);
	if (key == ESC)
		end_mrt(mrt);
	if (key == ENTER)
		ft_reinit(mrt);
	if (key == DEL)
		mrt->curr_obj = define_curr_obj(CAMERA, 0);
	cam_ctr(mrt, key);
	object_ctr(mrt, key);
	light_ctr(mrt, key);
	normalize(mrt->cam.dir);
	render_scene(mrt);
	return (key);
}
