/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_options2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 06:46:51 by gamoreno          #+#    #+#             */
/*   Updated: 2023/04/07 18:06:22 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	chess_ctr_plane(t_mrt *mrt, int key)
{
	if (key == PLUS)
		mrt->plane[mrt->curr_obj.index].option.chess_ctrl++;
	if (key == MINUS \
	&& mrt->plane[mrt->curr_obj.index].option.chess_ctrl > 0)
		mrt->plane[mrt->curr_obj.index].option.chess_ctrl--;
}

void	chess_ctr_sphere(t_mrt *mrt, int key)
{
	if (key == PLUS)
		mrt->sphere[mrt->curr_obj.index].option.chess_ctrl++;
	if (key == MINUS \
	&& mrt->sphere[mrt->curr_obj.index].option.chess_ctrl > 0)
		mrt->sphere[mrt->curr_obj.index].option.chess_ctrl--;
}

void	chess_ctr_cylinder(t_mrt *mrt, int key)
{
	if (key == PLUS)
		mrt->cylinder[mrt->curr_obj.index].option.chess_ctrl++;
	if (key == MINUS \
	&& mrt->cylinder[mrt->curr_obj.index].option.chess_ctrl > 0)
		mrt->cylinder[mrt->curr_obj.index].option.chess_ctrl--;
}

void	chess_ctr_cone(t_mrt *mrt, int key)
{
	if (key == PLUS)
		mrt->cone[mrt->curr_obj.index].option.chess_ctrl++;
	if (key == MINUS \
	&& mrt->cone[mrt->curr_obj.index].option.chess_ctrl > 0)
		mrt->cone[mrt->curr_obj.index].option.chess_ctrl--;
}

void	chess_ctr(t_mrt *mrt, int key)
{
	if (mrt->curr_obj.type == PLANE && mrt->curr_obj.chg_opt == CHECKERBOARD)
		chess_ctr_plane(mrt, key);
	if (mrt->curr_obj.type == SPHERE && mrt->curr_obj.chg_opt == CHECKERBOARD)
		chess_ctr_sphere(mrt, key);
	if (mrt->curr_obj.type == CYLINDER && mrt->curr_obj.chg_opt == CHECKERBOARD)
		chess_ctr_cylinder(mrt, key);
	if (mrt->curr_obj.type == CONE && mrt->curr_obj.chg_opt == CHECKERBOARD)
		chess_ctr_cone(mrt, key);
}
