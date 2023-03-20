/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:18:58 by ana               #+#    #+#             */
/*   Updated: 2023/03/20 18:28:21 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	end_mrt(t_mrt *mrt)
{
	(void)mrt;
	printf("%s\n", CLEAN_EXIT);
	ft_quit(EXIT_OK);
	return (0);
}

int	ft_controls(t_mrt *mrt)
{
	mlx_hook(mrt->win, 2, 1, key_press, mrt);
	mlx_hook(mrt->win, 17, 0, end_mrt, mrt);
	mlx_mouse_hook(mrt->win, &mouse_press, mrt);
	return (0);
}

int	main(int ac, char **av)
{
	t_mrt	mrt;

	if (ac != 2)
		return (printf("Usage: ./miniRT <scene.rt>\n"), 1);
	if (init_minirt(&mrt, av[1]))
		return (1);
	set_all_cam_values(&mrt.cam);
	pixel_calcul(&mrt);
	mlx_put_image_to_window(mrt.mlx, mrt.win, mrt.img, \
	((WX - IX) / 2) + BORDER, (WY - IY) / 2);
	ft_controls(&mrt);
	mlx_loop(mrt.mlx);
	return (0);
}
