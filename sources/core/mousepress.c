/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mousepress.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:53:14 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/23 05:06:03 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mouse_press(int button, int x, int y, t_mrt *mrt)
{
	t_vec	curr_dir;
	t_inter	inter;

	if (button == 1)
	{
		curr_dir = normalize(vec_rest(screen_pxl_by_indx(&mrt->cam, \
		x - BORDER, y), mrt->cam.pos));
		inter = check_intersections(mrt, mrt->cam.pos, curr_dir);
		if (inter.dist != -1)
		{
			mrt->curr_obj.type = inter.type;
			mrt->curr_obj.index = inter.index;
			mrt->curr_obj.chg_opt = CHECKERBOARD;
		}
		else
		{
			mrt->curr_obj.type = CAMERA;
			mrt->curr_obj.index = 0;
			mrt->curr_obj.chg_opt = NOTHING;
		}
	}
	render_scene(mrt);
	return (button);
}
