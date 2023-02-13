/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:51:49 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/13 21:35:51 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_init_mlx(t_mrt *mrt)
{
	mrt->mlx = mlx_init();
	if (!mrt->mlx)
		return (1);
	mrt->win = mlx_new_window(mrt->mlx, WX, WY, "MiniRT");
	if (!mrt->win)
		return (mlx_destroy_display(mrt->mlx), free(mrt->mlx), 1);
	mrt->img = mlx_new_image(mrt->mlx, IX, IY);
	if (!mrt->img)
		return (mlx_destroy_window(mrt->mlx, mrt->win), \
		mlx_destroy_display(mrt->mlx), free(mrt->mlx), 1);
	mrt->addr = mlx_get_data_addr(mrt->img, &mrt->bpp, &mrt->sizel, &mrt->endi);
	if (!mrt->addr)
		return (end_mrt(mrt), 1);
	return (0);
}

// int	init_objects(t_mrt *mrt)
// {
// 	mrt->cam = NULL;
// 	mrt->light = NULL;
// 	mrt->sphere = NULL;
// 	mrt->plane = NULL;
// 	mrt->cylinder = NULL;
// 	mrt->triangle = NULL;
// }

int	init_minirt(t_mrt *mrt)
{
	if (ft_init_mlx(mrt))
		return (printf("Problem initializing minilibx\n"), 1);
	// if (init_objects(mrt))
	// 	return (pritnf("Problem initializing objects\n"), 1);
	return (0);
}