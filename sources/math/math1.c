/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 21:53:22 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/05 21:12:31 by ana              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*if ctrl == 0, it passes radians to degrees, else it passes degrees
to radians */
double	rad_and_deg(double angle, int ctrl)
{
	if (ctrl == 0)
		return ((angle * 180) / PI);
	else
		return ((angle * PI) / 180);
}

double	int_pow(double basis, int exp)
{
	int		i;
	double	res;

	res = 1;
	i = 0;
	while (i < exp)
	{
		res *= basis;
		i++;
	}
	return (res);
}

t_vec	fill_coord(double c1, double c2, double c3)
{
	t_vec	res;

	res.x = c1;
	res.y = c2;
	res.z = c3;
	return (res);
}

double	vect_norm(t_vec v)
{
	return (sqrt(norm_raised_2(v)));
}

t_vec	normalize(t_vec v)
{
	t_vec	ret;
	double	norm;

	norm = vect_norm(v);
	ret.x = v.x / norm;
	ret.y = v.y / norm;
	ret.z = v.z / norm;
	return (ret);
}
