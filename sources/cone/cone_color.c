/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 07:27:52 by gamoreno          #+#    #+#             */
/*   Updated: 2023/04/05 09:09:30 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_c_chess	get_cone_bdy_col(t_mrt *mrt, int i, t_vec coor, t_rgb color)
// {
// 	t_c_chess	ret;
// 	double		aux_dist;

// 	ret.color = color;
// 	aux_dist = mrt->cone[i].height / 
// 	return (ret);
// }

t_rgb	get_cone_color(t_mrt *mrt, int i, t_vec *new, t_cuad_ctr ctr)
{
	t_rgb	ret;

	(void)new;
	(void)ctr;
	ret = mrt->cone[i].color;
	return (ret);
}