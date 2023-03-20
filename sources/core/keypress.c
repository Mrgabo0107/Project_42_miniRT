/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:25:02 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/20 18:46:16 by yridgway         ###   ########.fr       */
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

int	key_press(int key, t_mrt *mrt)
{
	if (key == ESC)
		end_mrt(mrt);
	if (mrt->curr_obj.type != CAMERA)
	{
		move_obj(mrt, key);
		rotate_obj(mrt, key);
	}
	if (key == ENTER)
		ft_reinit(mrt);
	if (key == DEL)
		define_cam_as_curr_obj(mrt);
	ft_move_cam(mrt, key);
	ft_change_cam_dir(mrt, key);
	normalize(mrt->cam.dir);
	// set_all_cam_values(&mrt->cam);
	render_scene(mrt);
	return (key);
}
