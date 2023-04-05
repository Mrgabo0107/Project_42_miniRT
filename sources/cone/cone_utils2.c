/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 07:27:52 by gamoreno          #+#    #+#             */
/*   Updated: 2023/04/05 08:12:38 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	contour_cone(t_mrt *mrt, t_vec *new, double c, double tang)
{
	t_discr	discr;
	double	radius;

	radius = mrt->cone[mrt->curr_obj.index].height * tang;
	discr = get_cone_disc(new, tang);
	if ((v_abs(discr.dscr) < 0.0008 * c * radius && !cam_in_cone(mrt, \
	mrt->curr_obj.index, new[0], tang)) || v_abs((new[0].z + (c * new[1].z))\
	- mrt->cone[mrt->curr_obj.index].height) < 0.05)
		return (1);
	return (0);
}

void	fov_ctr(t_mrt *mrt, int key)
{
	if (mrt->curr_obj.chg_opt == FOV)
	{
		if (key == PLUS && mrt->cone[mrt->curr_obj.index].angle < PI)
			mrt->cone[mrt->curr_obj.index].angle += 0.05;
		if (key == MINUS && mrt->cone[mrt->curr_obj.index].angle > 0.1)
			mrt->cone[mrt->curr_obj.index].angle -= 0.05;
	}
}
