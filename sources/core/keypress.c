/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:25:02 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/30 17:47:51 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_move_cam(t_mrt *mrt, int key)
{
	if (key == W)
		mrt->cam.pos = vec_sum(mrt->cam.pos, \
		scal_vec(0.5, mrt->cam.screen_base.n3));
	if (key == S)
		mrt->cam.pos = vec_sum(mrt->cam.pos, \
		scal_vec(-0.5, mrt->cam.screen_base.n3));
	if (key == A)
		mrt->cam.pos = vec_sum(mrt->cam.pos, \
		scal_vec(-0.5, mrt->cam.screen_base.n1));
	if (key == D)
		mrt->cam.pos = vec_sum(mrt->cam.pos, \
		scal_vec(0.5, mrt->cam.screen_base.n1));
	if (key == Q)
		mrt->cam.pos = vec_sum(mrt->cam.pos, \
		scal_vec(0.5, mrt->cam.screen_base.n2));
	if (key == E)
		mrt->cam.pos = vec_sum(mrt->cam.pos, \
		scal_vec(-0.5, mrt->cam.screen_base.n2));
}

void	ft_change_cam_dir(t_mrt *mrt, int key)
{
	if (key == UP)
		mrt->cam.dir = vec_sum(mrt->cam.dir, \
		scal_vec(-0.2, mrt->cam.screen_base.n2));
	if (key == DOWN)
		mrt->cam.dir = vec_sum(mrt->cam.dir, \
		scal_vec(0.2, mrt->cam.screen_base.n2));
	if (key == LEFT)
		mrt->cam.dir = vec_sum(mrt->cam.dir, \
		scal_vec(-0.2, mrt->cam.screen_base.n1));
	if (key == RIGHT)
		mrt->cam.dir = vec_sum(mrt->cam.dir, \
		scal_vec(0.2, mrt->cam.screen_base.n1));
}

void	define_curr_obj(t_mrt *mrt, int type, int index)
{
	mrt->curr_obj.index = index;
	mrt->curr_obj.type = type;
}

void	chess_ctr(t_mrt *mrt, int key)
{
	if (mrt->curr_obj.type == PLANE && mrt->curr_obj.chg_opt == CHECKERBOARD)
	{
		if (key == PLUS)
			mrt->plane[mrt->curr_obj.index].option.chess_ctrl++;
		if (key == MINUS \
		&& mrt->plane[mrt->curr_obj.index].option.chess_ctrl > 0)
			mrt->plane[mrt->curr_obj.index].option.chess_ctrl--;
	}
	if (mrt->curr_obj.type == SPHERE && mrt->curr_obj.chg_opt == CHECKERBOARD)
	{
		if (key == PLUS)
			mrt->sphere[mrt->curr_obj.index].option.chess_ctrl++;
		if (key == MINUS \
		&& mrt->sphere[mrt->curr_obj.index].option.chess_ctrl > 0)
			mrt->sphere[mrt->curr_obj.index].option.chess_ctrl--;
	}
	if (mrt->curr_obj.type == CYLINDER && mrt->curr_obj.chg_opt == CHECKERBOARD)
	{
		if (key == PLUS)
			mrt->cylinder[mrt->curr_obj.index].option.chess_ctrl++;
		if (key == MINUS \
		&& mrt->cylinder[mrt->curr_obj.index].option.chess_ctrl > 0)
			mrt->cylinder[mrt->curr_obj.index].option.chess_ctrl--;
	}
}

void	light_ctr(t_mrt *mrt, int key)
{
	if (key == PLUS && mrt->light[mrt->curr_obj.index].ratio < 1.0)
		mrt->light[mrt->curr_obj.index].ratio += 0.1;
	if (key == MINUS && mrt->light[mrt->curr_obj.index].ratio > 0.0)
		mrt->light[mrt->curr_obj.index].ratio -= 0.1;
}

int	key_press(int key, t_mrt *mrt)
{
	if (key == Z)
		return (save_scene(mrt), 0);
	if (key == X)
		return (write_to_ppm(mrt), 0);
	if (key == ESC)
		end_mrt(mrt);
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
	if (key == ENTER)
		ft_reinit(mrt);
	if (key == DEL)
		define_curr_obj(mrt, CAMERA, 0);
	if (mrt->curr_obj.type == LIGHT)
		light_ctr(mrt, key);
	if (key == L)
		define_curr_obj(mrt, LIGHT, \
		(mrt->curr_obj.index + 1) % mrt->obj_count[LIGHT]);
	ft_move_cam(mrt, key);
	ft_change_cam_dir(mrt, key);
	normalize(mrt->cam.dir);
	render_scene(mrt);
	return (key);
}
