/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:51:49 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/13 21:02:25 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_minirt(t_mrt *mrt)
{
	printf("ello\n");
	mrt->mlx = mlx_init();
	if (!mrt->mlx)
		return (1);
	mrt->win = mlx_new_window(mrt->mlx, WX, WY, "MiniRT");
	if (!mrt->win)
		return (1);
	mrt->img = mlx_new_image(mrt->mlx, IX, IY);
	if (!mrt->img)
		return (1);
	mrt->addr = mlx_get_data_addr(mrt->img, &mrt->bpp, &mrt->sizel, &mrt->endi);
	if (!mrt->addr)
		return (1);
	return (0);
}
