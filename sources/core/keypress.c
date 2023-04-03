/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel <yoel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:25:02 by gamoreno          #+#    #+#             */
/*   Updated: 2023/04/02 18:48:13 by yoel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	define_curr_obj(t_mrt *mrt, int type, int index)
{
	mrt->curr_obj.index = index;
	mrt->curr_obj.type = type;
}

void	light_ctr(t_mrt *mrt, int key)
{
	if (mrt->curr_obj.type == LIGHT)
	{
		if (key == PLUS && mrt->light[mrt->curr_obj.index].ratio < 1.0)
			mrt->light[mrt->curr_obj.index].ratio += 0.1;
		if (key == MINUS && mrt->light[mrt->curr_obj.index].ratio > 0.0)
			mrt->light[mrt->curr_obj.index].ratio -= 0.1;
	}
	if (key == L)
		define_curr_obj(mrt, LIGHT, \
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
		bump_option(mrt, key);
	}
}

int	key_press(int key, t_mrt *mrt)
{
	if (key == Z)
		return (save_scene(mrt), 0);
	if (key == X)
		return (write_to_ppm(mrt, BORDER), 0);
	if (key == ESC)
		end_mrt(mrt);
	if (key == ENTER)
		ft_reinit(mrt);
	if (key == DEL)
		define_curr_obj(mrt, CAMERA, 0);
	cam_ctr(mrt, key);
	object_ctr(mrt, key);
	light_ctr(mrt, key);
	normalize(mrt->cam.dir);
	render_scene(mrt);
	return (key);
}
