/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chosen_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:50:27 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/16 01:11:21 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void print_vector(t_vec v)
{
	printf("[%f, %f, %f]\n", v.x, v.y, v.z);
}

t_rgb	check_plane_grid(t_mrt *mrt, int x, int y, t_rgb color)
{
	t_vec	curr_dir;
	double	c;
	t_vec	inter;
	t_mtrx	chg_b;
	t_rgb	ret;

	ret = color;
	curr_dir = normalize(vec_rest(screen_pxl_by_indx(&mrt->cam, x, y),
				mrt->cam.pos));
	c = distance_to_plane(mrt->cam.pos, mrt->plane[mrt->curr_obj.index].pos,
			mrt->plane[mrt->curr_obj.index].dir, curr_dir);
	if (c > 0)
	{
		chg_b = fill_mtrx(mrt->plane[mrt->curr_obj.index].base.n1,
				mrt->plane[mrt->curr_obj.index].base.n2,
				mrt->plane[mrt->curr_obj.index].base.n3);
		inter = mtrx_by_vec(chg_b,
				vec_sum(mrt->cam.pos, scal_vec(c, curr_dir)));
		if (v_abs(decimal_part(inter.x )) * c / 2 < 0.007 * c
			|| v_abs(decimal_part(inter.y)) * c / 2 < 0.007 * c)
			ret = get_opposite_color(ret);
	}
	return (ret);
}

// t_rgb	check_sphere_contour(t_mrt *mrt, int x, int y, t_rgb color)
// {
	
// }

// t_rgb	check_cylinder_contour(t_mrt *mrt, int x, int y, t_rgb color)
// {
	
// }

t_rgb	chosen_obj(t_mrt *mrt, int x, int y, t_rgb color)
{
	t_rgb	ret;

	ret = color;
	if (mrt->curr_obj.type == PLANE)
		ret = check_plane_grid(mrt, x, y, color);
	// if (mrt->curr_obj.type == SPHERE)
	// 	ret = check_sphere_contour(mrt, x, y, color);
	// if (mrt->curr_obj.type == CYLINDER)
	// 	ret = check_cylinder_contour(mrt, x, y, color);
	return (ret);
}