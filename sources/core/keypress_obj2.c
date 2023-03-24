/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_obj2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 03:43:09 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/24 22:24:45 by yridgway         ###   ########.fr       */
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

void	rotate_cyl(t_mrt *mrt, int key, double an)
{
	if (key == I)
		mrt->cylinder[mrt->curr_obj.index].base
			= general_rotation(mrt->cylinder[mrt->curr_obj.index].base, 1, an);
	if (key == O)
		mrt->cylinder[mrt->curr_obj.index].base
			= general_rotation(mrt->cylinder[mrt->curr_obj.index].base, 1, -an);
	if (key == J)
		mrt->cylinder[mrt->curr_obj.index].base
			= general_rotation(mrt->cylinder[mrt->curr_obj.index].base, 2, an);
	if (key == K)
		mrt->cylinder[mrt->curr_obj.index].base
			= general_rotation(mrt->cylinder[mrt->curr_obj.index].base, 2, -an);
	if (key == N)
		mrt->cylinder[mrt->curr_obj.index].base
			= general_rotation(mrt->cylinder[mrt->curr_obj.index].base, 3, an);
	if (key == M)
		mrt->cylinder[mrt->curr_obj.index].base
			= general_rotation(mrt->cylinder[mrt->curr_obj.index].base, 3, -an);
	mrt->cylinder[mrt->curr_obj.index].dir
		= mrt->cylinder[mrt->curr_obj.index].base.n3;
}

void	rotate_obj(t_mrt *mrt, int key)
{
	double	angl;

	angl = rad_and_deg(10, 1);
	if (mrt->curr_obj.type == PLANE)
		rotate_plane(mrt, key, angl);
	if (mrt->curr_obj.type == CYLINDER)
		rotate_cyl(mrt, key, angl);
}
