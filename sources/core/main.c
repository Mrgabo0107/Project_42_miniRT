/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/02/27 19:25:33 by ana              ###   ########.fr       */
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

int	key_press(int key, t_mrt *mrt)
{
	// printf("\n\nkey: %d\n\n", key);
	// ft_putnum_fd(1, key);
	if (key == ESC)
		end_mrt(mrt);
	if (key == W)
		mrt->cam.pos = vec_sum(mrt->cam.pos, scal_vec(0.5, mrt->cam.screen_base.n3));
	if (key == S)
		mrt->cam.pos = vec_sum(mrt->cam.pos, scal_vec(-0.5, mrt->cam.screen_base.n3));
	if (key == A)
		mrt->cam.pos = vec_sum(mrt->cam.pos, scal_vec(-0.5, mrt->cam.screen_base.n1));
	if (key == D)
		mrt->cam.pos = vec_sum(mrt->cam.pos, scal_vec(0.5, mrt->cam.screen_base.n1));
	if (key == Q)
		mrt->cam.pos = vec_sum(mrt->cam.pos, scal_vec(0.5, mrt->cam.screen_base.n2));
	if (key == E)
		mrt->cam.pos = vec_sum(mrt->cam.pos, scal_vec(-0.5, mrt->cam.screen_base.n2));
	if (key == UP)
		mrt->cam.dir = vec_sum(mrt->cam.dir, scal_vec(-0.2, mrt->cam.screen_base.n2));
	if (key == DOWN)
		mrt->cam.dir = vec_sum(mrt->cam.dir, scal_vec(0.2, mrt->cam.screen_base.n2));
	if (key == LEFT)
		mrt->cam.dir = vec_sum(mrt->cam.dir, scal_vec(-0.2, mrt->cam.screen_base.n1));
	if (key == RIGHT)
		mrt->cam.dir = vec_sum(mrt->cam.dir, scal_vec(0.2, mrt->cam.screen_base.n1));
	normalize(mrt->cam.dir);
	set_all_cam_values(&mrt->cam);
	pixel_calcul(mrt);
	mlx_put_image_to_window(mrt->mlx, mrt->win, mrt->img, 0, 0);
	printf("cam pos: %f %f %f\n", mrt->cam.pos.x, mrt->cam.pos.y, mrt->cam.pos.z);
	printf("cam dir: %f %f %f\n", mrt->cam.dir.x, mrt->cam.dir.y, mrt->cam.dir.z);
	return (key);
}

int	ft_controls(t_mrt *mrt)
{
	// mlx_key_hook(mrt->win, &key_press, mrt);
	mlx_hook(mrt->win, 2, 1, key_press, mrt);
	mlx_hook(mrt->win, 17, 0, end_mrt, mrt);
	return (0);
}

int	main(int ac, char **ag)
{
	t_mrt	mrt;

	(void)ag;
	if (ac != 2)
		return (printf("Usage: ./miniRT <scene.rt>\n"), 1);
	if (init_minirt(&mrt))
		return (1);
	if (ft_parse(&mrt, ag[1]))
		return (printf("Error\n"), 1);
	printf("Done parsing\n");
	ft_printf_objects(&mrt);
	// print_pixels_coord(&mrt.cam);
	set_all_cam_values(&mrt.cam);
	pixel_calcul(&mrt);
	mlx_put_image_to_window(mrt.mlx, mrt.win, mrt.img, 0, 0);
	ft_controls(&mrt);
	mlx_loop(mrt.mlx);
	return (0);
}
