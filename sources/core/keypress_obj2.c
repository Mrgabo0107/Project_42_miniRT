/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_obj2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 03:43:09 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/22 20:21:17 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rotate_plane(t_mrt *mrt, int key, double angl)
{
	if (key == I)
		mrt->plane[mrt->curr_obj.index].base
			= general_rotation(mrt->plane[mrt->curr_obj.index].base, 1, angl);
	if (key == O)
		mrt->plane[mrt->curr_obj.index].base
			= general_rotation(mrt->plane[mrt->curr_obj.index].base, 1, -angl);
	if (key == J)
		mrt->plane[mrt->curr_obj.index].base
			= general_rotation(mrt->plane[mrt->curr_obj.index].base, 2, angl);
	if (key == K)
		mrt->plane[mrt->curr_obj.index].base
			= general_rotation(mrt->plane[mrt->curr_obj.index].base, 2, -angl);
	if (key == N)
		mrt->plane[mrt->curr_obj.index].base
			= general_rotation(mrt->plane[mrt->curr_obj.index].base, 3, angl);
	if (key == M)
		mrt->plane[mrt->curr_obj.index].base
			= general_rotation(mrt->plane[mrt->curr_obj.index].base, 3, -angl);
	mrt->plane[mrt->curr_obj.index].dir
		= mrt->plane[mrt->curr_obj.index].base.n3;
}

void	rotate_sphere(t_mrt *mrt, int key, double angl)
{
	if (key == I)
		mrt->sphere[mrt->curr_obj.index].base
			= general_rotation(mrt->sphere[mrt->curr_obj.index].base, 1, angl);
	if (key == O)
		mrt->sphere[mrt->curr_obj.index].base
			= general_rotation(mrt->sphere[mrt->curr_obj.index].base, 1, -angl);
	if (key == J)
		mrt->sphere[mrt->curr_obj.index].base
			= general_rotation(mrt->sphere[mrt->curr_obj.index].base, 2, angl);
	if (key == K)
		mrt->sphere[mrt->curr_obj.index].base
			= general_rotation(mrt->sphere[mrt->curr_obj.index].base, 2, -angl);
	if (key == N)
		mrt->sphere[mrt->curr_obj.index].base
			= general_rotation(mrt->sphere[mrt->curr_obj.index].base, 3, angl);
	if (key == M)
		mrt->sphere[mrt->curr_obj.index].base
			= general_rotation(mrt->sphere[mrt->curr_obj.index].base, 3, -angl);
	mrt->sphere[mrt->curr_obj.index].dir
		= mrt->sphere[mrt->curr_obj.index].base.n3;
}

void	rotate_cyl(t_mrt *mrt, int key, double angl)
{
	if (key == I)
		mrt->cylinder[mrt->curr_obj.index].base
			= general_rotation(mrt->cylinder[mrt->curr_obj.index].base, 1,
				angl);
	if (key == O)
		mrt->cylinder[mrt->curr_obj.index].base
			= general_rotation(mrt->cylinder[mrt->curr_obj.index].base, 1,
				-angl);
	if (key == J)
		mrt->cylinder[mrt->curr_obj.index].base
			= general_rotation(mrt->cylinder[mrt->curr_obj.index].base, 2,
				angl);
	if (key == K)
		mrt->cylinder[mrt->curr_obj.index].base
			= general_rotation(mrt->cylinder[mrt->curr_obj.index].base, 2,
				-angl);
	if (key == N)
		mrt->cylinder[mrt->curr_obj.index].base
			= general_rotation(mrt->cylinder[mrt->curr_obj.index].base, 3,
				angl);
	if (key == M)
		mrt->cylinder[mrt->curr_obj.index].base
			= general_rotation(mrt->cylinder[mrt->curr_obj.index].base, 3,
				-angl);
	mrt->cylinder[mrt->curr_obj.index].dir
		= mrt->cylinder[mrt->curr_obj.index].base.n3;
}

void	rotate_obj(t_mrt *mrt, int key)
{
	double	angl;

	angl = rad_and_deg(10, 1);
	if (mrt->curr_obj.type == PLANE)
		rotate_plane(mrt, key, angl);
	if (mrt->curr_obj.type == SPHERE)
		rotate_sphere(mrt, key, angl);
	if (mrt->curr_obj.type == CYLINDER)
		rotate_cyl(mrt, key, angl);
}
