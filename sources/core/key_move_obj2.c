/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_move_obj2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 03:43:09 by gamoreno          #+#    #+#             */
/*   Updated: 2023/04/05 05:00:10 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	move_cone(t_mrt *mrt, int key)
{
	if (key == OBJBEHIND)
		mrt->cone[mrt->curr_obj.index].pos
			= vec_sum(mrt->cone[mrt->curr_obj.index].pos,
				mrt->cam.screen_base.n3);
	if (key == OBJFRONT)
		mrt->cone[mrt->curr_obj.index].pos
			= vec_rest(mrt->cone[mrt->curr_obj.index].pos,
				mrt->cam.screen_base.n3);
	if (key == OBJLEFT)
		mrt->cone[mrt->curr_obj.index].pos
			= vec_rest(mrt->cone[mrt->curr_obj.index].pos,
				mrt->cam.screen_base.n1);
	if (key == OBJRIGHT)
		mrt->cone[mrt->curr_obj.index].pos
			= vec_sum(mrt->cone[mrt->curr_obj.index].pos,
				mrt->cam.screen_base.n1);
	if (key == OBJDOWN)
		mrt->cone[mrt->curr_obj.index].pos
			= vec_sum(mrt->cone[mrt->curr_obj.index].pos,
				mrt->cam.screen_base.n2);
	if (key == OBJUP)
		mrt->cone[mrt->curr_obj.index].pos
			= vec_rest(mrt->cone[mrt->curr_obj.index].pos,
				mrt->cam.screen_base.n2);
}
