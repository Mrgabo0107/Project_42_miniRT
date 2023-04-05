/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chosen_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:50:27 by gamoreno          #+#    #+#             */
/*   Updated: 2023/04/05 07:06:45 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	check_plane_grid(t_mrt *mrt, t_vec	curr_dir, t_rgb color)
{
	double	c;
	t_vec	inter;
	t_mtrx	chg_b;
	t_rgb	ret;
	t_vec	new_cam;

	ret = color;
	new_cam = vec_rest(mrt->cam.pos, mrt->plane[mrt->curr_obj.index].pos);
	c = distance_to_plane(mrt->cam.pos, mrt->plane[mrt->curr_obj.index].pos,
			mrt->plane[mrt->curr_obj.index].dir, curr_dir);
	if (c > 0)
	{
		chg_b = fill_mtrx(mrt->plane[mrt->curr_obj.index].base.n1,
				mrt->plane[mrt->curr_obj.index].base.n2,
				mrt->plane[mrt->curr_obj.index].base.n3);
		inter = mtrx_by_vec(chg_b,
				vec_sum(new_cam, scal_vec(c, curr_dir)));
		if (v_abs(decimal_part(inter.x)) * c / 2 < 0.002 * c * c
			|| v_abs(decimal_part(inter.y)) * c / 2 < 0.002 * c * c)
			ret = get_opposite_color(ret);
	}
	return (ret);
}

t_rgb	check_sphere_contour(t_mrt *mrt, t_vec curr_dir, t_rgb color)
{
	t_rgb	ret;
	double	c;
	t_discr	discr;
	t_vec	new_cam;

	ret = color;
	new_cam = vec_rest(mrt->cam.pos, mrt->sphere[mrt->curr_obj.index].center);
	discr = get_sph_dscr(new_cam, curr_dir,
			int_pow(mrt->sphere[mrt->curr_obj.index].radius, 2));
	c = solve_quad(&discr);
	if (v_abs(discr.dscr) < \
	(0.01 * c * mrt->sphere[mrt->curr_obj.index].radius))
		ret = get_opposite_color(ret);
	return (ret);
}

int	contour_cyl(t_mrt *mrt, t_vec new_cam, t_vec new_dir, double c)
{
	t_discr	discr;

	discr = get_cyl_disc(mrt->cylinder[mrt->curr_obj.index], new_cam, new_dir);
	if ((v_abs(discr.dscr) < 0.02 * c
			* mrt->cylinder[mrt->curr_obj.index].radius
			&& !cam_in_cyl(mrt, mrt->curr_obj.index, new_cam))
		|| v_abs(v_abs(new_cam.z + (c * new_dir.z))
			- (mrt->cylinder[mrt->curr_obj.index].height / 2)) < 0.01)
		return (1);
	return (0);
}

t_rgb	check_cylinder_contour(t_mrt *mrt, t_vec curr_dir, t_rgb color)
{
	t_cuad_ctr		ctr;
	t_vec			new_cam;
	t_vec			new_dir;
	t_mtrx			chg_base;

	new_cam = vec_rest(mrt->cam.pos, mrt->cylinder[mrt->curr_obj.index].pos);
	chg_base = fill_mtrx(mrt->cylinder[mrt->curr_obj.index].base.n1,
			mrt->cylinder[mrt->curr_obj.index].base.n2,
			mrt->cylinder[mrt->curr_obj.index].base.n3);
	new_cam = mtrx_by_vec(chg_base, new_cam);
	new_dir = mtrx_by_vec(chg_base, curr_dir);
	ctr = get_dist_to_cyl(mrt->cylinder[mrt->curr_obj.index], new_cam, new_dir);
	if (ctr.c > 0)
	{
		if (((ctr.cap_ctrl == 1 || ctr.cap_ctrl == 2)
				&& v_abs((int_pow(new_cam.x + (ctr.c * new_dir.x), 2)
						+ int_pow(new_cam.y + (ctr.c * new_dir.y), 2))
					- int_pow(mrt->cylinder[mrt->curr_obj.index].radius, 2))
				< 0.009 * ctr.c * mrt->cylinder[mrt->curr_obj.index].radius)
			|| (ctr.cap_ctrl == 3
				&& contour_cyl(mrt, new_cam, new_dir, ctr.c)))
			return (get_opposite_color(color));
	}
	return (color);
}

t_rgb	chosen_obj(t_mrt *mrt, int x, int y, t_rgb color)
{
	t_rgb	ret;
	t_vec	curr_dir;

	ret = color;
	curr_dir = normalize(vec_rest(screen_pxl_by_indx(mrt, &mrt->cam, x, y),
				mrt->cam.pos));
	if (mrt->curr_obj.type == PLANE)
		ret = check_plane_grid(mrt, curr_dir, color);
	if (mrt->curr_obj.type == SPHERE)
		ret = check_sphere_contour(mrt, curr_dir, color);
	if (mrt->curr_obj.type == CYLINDER)
		ret = check_cylinder_contour(mrt, curr_dir, color);
	if (mrt->curr_obj.type == CONE)
		ret = check_cone_contour(mrt, curr_dir, color);
	return (ret);
}
