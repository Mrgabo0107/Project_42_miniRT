/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_obj3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 06:46:51 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/24 22:16:51 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	chg_options(t_mrt *mrt, int key)
{
	if (key == H && mrt->curr_obj.type != PLANE && mrt->curr_obj.type != SPHERE)
		mrt->curr_obj.chg_opt = HEIGHT;
	if (key == R && mrt->curr_obj.type != PLANE)
		mrt->curr_obj.chg_opt = RADIUS;
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
	}
}
