/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_obj1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 03:43:09 by gamoreno          #+#    #+#             */
/*   Updated: 2023/04/04 19:22:05 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	move_plane(t_mrt *mrt, int key)
{
	if (key == OBJBEHIND)
		mrt->plane[mrt->curr_obj.index].pos
			= vec_sum(mrt->plane[mrt->curr_obj.index].pos,
				mrt->cam.screen_base.n3);
	if (key == OBJFRONT)
		mrt->plane[mrt->curr_obj.index].pos
			= vec_rest(mrt->plane[mrt->curr_obj.index].pos,
				mrt->cam.screen_base.n3);
	if (key == OBJLEFT)
		mrt->plane[mrt->curr_obj.index].pos
			= vec_rest(mrt->plane[mrt->curr_obj.index].pos,
				mrt->cam.screen_base.n1);
	if (key == OBJRIGHT)
		mrt->plane[mrt->curr_obj.index].pos
			= vec_sum(mrt->plane[mrt->curr_obj.index].pos,
				mrt->cam.screen_base.n1);
	if (key == OBJDOWN)
		mrt->plane[mrt->curr_obj.index].pos
			= vec_sum(mrt->plane[mrt->curr_obj.index].pos,
				mrt->cam.screen_base.n2);
	if (key == OBJUP)
		mrt->plane[mrt->curr_obj.index].pos
			= vec_rest(mrt->plane[mrt->curr_obj.index].pos,
				mrt->cam.screen_base.n2);
}

void	move_sphere(t_mrt *mrt, int key)
{
	if (key == OBJBEHIND)
		mrt->sphere[mrt->curr_obj.index].center
			= vec_sum(mrt->sphere[mrt->curr_obj.index].center,
				mrt->cam.screen_base.n3);
	if (key == OBJFRONT)
		mrt->sphere[mrt->curr_obj.index].center
			= vec_rest(mrt->sphere[mrt->curr_obj.index].center,
				mrt->cam.screen_base.n3);
	if (key == OBJLEFT)
		mrt->sphere[mrt->curr_obj.index].center
			= vec_rest(mrt->sphere[mrt->curr_obj.index].center,
				mrt->cam.screen_base.n1);
	if (key == OBJRIGHT)
		mrt->sphere[mrt->curr_obj.index].center
			= vec_sum(mrt->sphere[mrt->curr_obj.index].center,
				mrt->cam.screen_base.n1);
	if (key == OBJDOWN)
		mrt->sphere[mrt->curr_obj.index].center
			= vec_sum(mrt->sphere[mrt->curr_obj.index].center,
				mrt->cam.screen_base.n2);
	if (key == OBJUP)
		mrt->sphere[mrt->curr_obj.index].center
			= vec_rest(mrt->sphere[mrt->curr_obj.index].center,
				mrt->cam.screen_base.n2);
}

void	move_cyl(t_mrt *mrt, int key)
{
	if (key == OBJBEHIND)
		mrt->cylinder[mrt->curr_obj.index].pos
			= vec_sum(mrt->cylinder[mrt->curr_obj.index].pos,
				mrt->cam.screen_base.n3);
	if (key == OBJFRONT)
		mrt->cylinder[mrt->curr_obj.index].pos
			= vec_rest(mrt->cylinder[mrt->curr_obj.index].pos,
				mrt->cam.screen_base.n3);
	if (key == OBJLEFT)
		mrt->cylinder[mrt->curr_obj.index].pos
			= vec_rest(mrt->cylinder[mrt->curr_obj.index].pos,
				mrt->cam.screen_base.n1);
	if (key == OBJRIGHT)
		mrt->cylinder[mrt->curr_obj.index].pos
			= vec_sum(mrt->cylinder[mrt->curr_obj.index].pos,
				mrt->cam.screen_base.n1);
	if (key == OBJDOWN)
		mrt->cylinder[mrt->curr_obj.index].pos
			= vec_sum(mrt->cylinder[mrt->curr_obj.index].pos,
				mrt->cam.screen_base.n2);
	if (key == OBJUP)
		mrt->cylinder[mrt->curr_obj.index].pos
			= vec_rest(mrt->cylinder[mrt->curr_obj.index].pos,
				mrt->cam.screen_base.n2);
}

void	move_light(t_mrt *mrt, int key)
{
	if (key == OBJBEHIND)
		mrt->light.pos
			= vec_sum(mrt->light.pos,
				mrt->cam.screen_base.n3);
	if (key == OBJFRONT)
		mrt->light.pos
			= vec_rest(mrt->light.pos,
				mrt->cam.screen_base.n3);
	if (key == OBJLEFT)
		mrt->light.pos
			= vec_rest(mrt->light.pos,
				mrt->cam.screen_base.n1);
	if (key == OBJRIGHT)
		mrt->light.pos
			= vec_sum(mrt->light.pos,
				mrt->cam.screen_base.n1);
	if (key == OBJDOWN)
		mrt->light.pos
			= vec_sum(mrt->light.pos,
				mrt->cam.screen_base.n2);
	if (key == OBJUP)
		mrt->light.pos
			= vec_rest(mrt->light.pos,
				mrt->cam.screen_base.n2);
}

void	move_obj(t_mrt *mrt, int key)
{
	if (mrt->curr_obj.type == PLANE)
		move_plane(mrt, key);
	if (mrt->curr_obj.type == SPHERE)
		move_sphere(mrt, key);
	if (mrt->curr_obj.type == CYLINDER)
		move_cyl(mrt, key);
	if (mrt->curr_obj.type == LIGHT)
		move_light(mrt, key);
}
