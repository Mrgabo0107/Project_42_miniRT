/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:12:22 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/13 15:41:04 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static int	init(t_mrt *mrt)
{
	mrt->mlx = mlx_init();
	if (!mrt->mlx)
		return(1);
	mrt->win = mlx_new_window(mrt->mlx, WX, WY, "MiniRT");
	if (!mrt->win)
		return(1);
	mrt->img = mlx_new_image(mrt->mlx, IX, IY);
	if (!mrt->img)
		return (1);
	mrt->addr = mlx_get_data_addr(mrt->img, &mrt->bpp, &mrt->sizel, &mrt->endi);
	if (!mrt->addr)
		return (1);
	return (0);
}

static int end_mrt(void *mrt)
{
	(void)mrt;
	exit(0);
}

static int key_press(int key, void *mrt)
{
	// printf("key: %d\n", key);
	if (key == 65307)
		end_mrt(mrt);
	return (key);
}

int main(int ac, char **ag)
{
	t_mrt	mrt;

	if(ac == 1)
	{
		(void)ag;
		if(init(&mrt))
			return(1);
		mlx_key_hook(mrt.win, &key_press, &mrt);
		mlx_hook(mrt.win, 17, 0, end_mrt, &mrt);
		mlx_loop(mrt.mlx);
	}
	return (0);
}