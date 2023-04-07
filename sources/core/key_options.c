/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 06:46:51 by gamoreno          #+#    #+#             */
/*   Updated: 2023/04/07 17:13:57 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	chg_options(t_mrt *mrt, int key)
{
	if (key == C)
		mrt->curr_obj.chg_opt = CHECKERBOARD;
	if (key == H && mrt->curr_obj.type != PLANE && mrt->curr_obj.type != SPHERE)
		mrt->curr_obj.chg_opt = HEIGHT;
	if (key == R && mrt->curr_obj.type != PLANE)
		mrt->curr_obj.chg_opt = RADIUS;
	if (key == F && mrt->curr_obj.type == CONE)
		mrt->curr_obj.chg_opt = FOV;
}

void	radius_ctr(t_mrt *mrt, int key)
{
	if (mrt->curr_obj.chg_opt == RADIUS)
	{
		if (key == PLUS && mrt->curr_obj.type == SPHERE)
			mrt->sphere[mrt->curr_obj.index].radius += 0.3;
		if (key == PLUS && mrt->curr_obj.type == CYLINDER)
			mrt->cylinder[mrt->curr_obj.index].radius += 0.3;
		if (key == MINUS && mrt->curr_obj.type == SPHERE
			&& mrt->sphere[mrt->curr_obj.index].radius > 0.3)
			mrt->sphere[mrt->curr_obj.index].radius -= 0.3;
		if (key == MINUS && mrt->curr_obj.type == CYLINDER
			&& mrt->cylinder[mrt->curr_obj.index].radius > 0.3)
		mrt->cylinder[mrt->curr_obj.index].radius -= 0.3;
	}
}

void	height_ctr(t_mrt *mrt, int key)
{
	if (mrt->curr_obj.chg_opt == HEIGHT)
	{
		if (key == PLUS && mrt->curr_obj.type == CYLINDER)
			mrt->cylinder[mrt->curr_obj.index].height += 0.3;
		if (key == MINUS && mrt->curr_obj.type == CYLINDER
			&& mrt->cylinder[mrt->curr_obj.index].height > 0.3)
		mrt->cylinder[mrt->curr_obj.index].height -= 0.3;
		if (key == PLUS && mrt->curr_obj.type == CONE)
			mrt->cone[mrt->curr_obj.index].height += 0.3;
		if (key == MINUS && mrt->curr_obj.type == CONE
			&& mrt->cone[mrt->curr_obj.index].height > 0.3)
		mrt->cone[mrt->curr_obj.index].height -= 0.3;
	}
}

void	bump_option(t_mrt *mrt, int key)
{
	if (key == B && mrt->curr_obj.type == PLANE
		&& mrt->plane[mrt->curr_obj.index].option.bump_map.path)
		mrt->plane[mrt->curr_obj.index].option.b_mp_ctrl
			= (mrt->plane[mrt->curr_obj.index].option.b_mp_ctrl + 1) % 2;
	if (key == B && mrt->curr_obj.type == SPHERE
		&& mrt->sphere[mrt->curr_obj.index].option.bump_map.path)
		mrt->sphere[mrt->curr_obj.index].option.b_mp_ctrl
			= (mrt->sphere[mrt->curr_obj.index].option.b_mp_ctrl + 1) % 2;
	if (key == B && mrt->curr_obj.type == CYLINDER
		&& mrt-> cylinder[mrt->curr_obj.index].option.bump_map.path)
		mrt-> cylinder[mrt->curr_obj.index].option.b_mp_ctrl
			= (mrt-> cylinder[mrt->curr_obj.index].option.b_mp_ctrl + 1) % 2;
	if (key == B && mrt->curr_obj.type == CONE
		&& mrt-> cone[mrt->curr_obj.index].option.bump_map.path)
		mrt-> cone[mrt->curr_obj.index].option.b_mp_ctrl
			= (mrt-> cone[mrt->curr_obj.index].option.b_mp_ctrl + 1) % 2;
}

void	texture_option(t_mrt *mrt, int key)
{
	if (key == T && mrt->curr_obj.type == PLANE
		&& mrt->plane[mrt->curr_obj.index].option.texture.path)
		mrt->plane[mrt->curr_obj.index].option.texture_ctrl
			= (mrt->plane[mrt->curr_obj.index].option.texture_ctrl + 1) % 2;
	if (key == T && mrt->curr_obj.type == SPHERE
		&& mrt->sphere[mrt->curr_obj.index].option.texture.path)
		mrt->sphere[mrt->curr_obj.index].option.texture_ctrl
			= (mrt->sphere[mrt->curr_obj.index].option.texture_ctrl + 1) % 2;
	if (key == T && mrt->curr_obj.type == CYLINDER
		&& mrt-> cylinder[mrt->curr_obj.index].option.texture.path)
		mrt-> cylinder[mrt->curr_obj.index].option.texture_ctrl
			= (mrt-> cylinder[mrt->curr_obj.index].option.texture_ctrl + 1) % 2;
	if (key == T && mrt->curr_obj.type == CONE
		&& mrt-> cone[mrt->curr_obj.index].option.texture.path)
		mrt-> cone[mrt->curr_obj.index].option.texture_ctrl
			= (mrt-> cone[mrt->curr_obj.index].option.texture_ctrl + 1) % 2;
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
	if (mrt->curr_obj.type == CONE && mrt->curr_obj.chg_opt == CHECKERBOARD)
	{
		if (key == PLUS)
			mrt->cone[mrt->curr_obj.index].option.chess_ctrl++;
		if (key == MINUS \
		&& mrt->cone[mrt->curr_obj.index].option.chess_ctrl > 0)
			mrt->cone[mrt->curr_obj.index].option.chess_ctrl--;
	}
}
