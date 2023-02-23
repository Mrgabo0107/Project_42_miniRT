/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 23:44:14 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/23 04:05:45 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	vec_rest(t_vec v1, t_vec v2)
{
	return (vec_sum(v1, scal_vector(-1, v2)));
}

double  max_v(double d1, double d2)
{
    if (d1 >= d2)
        return (d1);
    return (d2);    
}
