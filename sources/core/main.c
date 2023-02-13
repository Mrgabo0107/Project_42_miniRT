/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:12:22 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/13 19:07:17 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init(t_mrt *mrt)
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

int	end_mrt(t_mrt *mrt)
{
	mlx_destroy_image(mrt->mlx, mrt->img);
	mlx_destroy_window(mrt->mlx, mrt->win);
	mlx_destroy_display(mrt->mlx);
	free(mrt->mlx);
	exit(0);
}

int	key_press(int key, t_mrt *mrt)
{
	// printf("key: %d\n", key);
	if (key == 65307)
		end_mrt(mrt);
	return (key);
}

int	ft_controls(t_mrt *mrt)
{
	mlx_key_hook(mrt->win, &key_press, mrt);
	mlx_hook(mrt->win, 17, 0, end_mrt, mrt);
	return (0);
}

int	main(int ac, char **ag)
{
	t_mrt	mrt;

	if (ac == 1)
	{
		(void)ag;
		if (init(&mrt))
			return (1);
		ft_controls(&mrt);
		mlx_loop(mrt.mlx);
	}
	return (0);
}
