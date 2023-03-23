/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:25:02 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/23 00:57:51 by gamoreno         ###   ########.fr       */
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

void	define_cam_as_curr_obj(t_mrt *mrt)
{
	mrt->curr_obj.index = 0;
	mrt->curr_obj.type = CAMERA;
}

void	chess_ctr(t_mrt *mrt, int key)
{
	if (mrt->curr_obj.type == PLANE)
	{
		if (key == PLUS)
			mrt->plane[mrt->curr_obj.index].chess_ctrl++;
		if (key == MINUS && mrt->plane[mrt->curr_obj.index].chess_ctrl > 0)
			mrt->plane[mrt->curr_obj.index].chess_ctrl--;
	}
	if (mrt->curr_obj.type == SPHERE)
	{
		if (key == PLUS)
			mrt->sphere[mrt->curr_obj.index].chess_ctrl++;
		if (key == MINUS && mrt->sphere[mrt->curr_obj.index].chess_ctrl > 0)
			mrt->sphere[mrt->curr_obj.index].chess_ctrl--;
	}
}

int	key_press(int key, t_mrt *mrt)
{
	if (key == ESC)
		end_mrt(mrt);
	if (mrt->curr_obj.type != CAMERA)
	{
		move_obj(mrt, key);
		rotate_obj(mrt, key);
		chess_ctr(mrt, key);
	}
	if (key == ENTER)
		ft_reinit(mrt);
	if (key == DEL)
		define_cam_as_curr_obj(mrt);
	ft_move_cam(mrt, key);
	ft_change_cam_dir(mrt, key);
	normalize(mrt->cam.dir);
	set_all_cam_values(&mrt->cam);
	pixel_calcul(mrt);
	mlx_put_image_to_window(mrt->mlx, mrt->win, mrt->img, 0, 0);
	return (key);
}
