/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mousepress.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:53:14 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/20 18:22:32 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mouse_press(int button, int x, int y, t_mrt *mrt)
{
	t_vec	curr_dir;
	t_inter	inter;

	if (button == 1)
	{
		curr_dir = normalize(vec_rest(screen_pxl_by_indx(&mrt->cam, x, y),
					mrt->cam.pos));
		inter = check_intersections(mrt, mrt->cam.pos, curr_dir);
		if (inter.dist != -1)
		{
			mrt->curr_obj.type = inter.type;
			mrt->curr_obj.index = inter.index;
		}
		else
		{
			mrt->curr_obj.type = CAMERA;
			mrt->curr_obj.index = 0;
		}
	}
	pixel_calcul(mrt);
	mlx_put_image_to_window(mrt->mlx, mrt->win, mrt->img, ((WX - IX) / 2) + BORDER, (WY - IY) / 2);
	return (button);
}
