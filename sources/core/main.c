/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:18:58 by ana               #+#    #+#             */
/*   Updated: 2023/03/31 19:39:14 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	write_to_ppm(t_mrt *mrt)
{
	int				i;
	unsigned char	color[3];
	FILE			*fp;

	write(1, "writing to file... ", 19);
	fp = fopen("bump.ppm", "wb");
	fprintf(fp, "P6\n%d %d\n255\n", mrt->ix, mrt->iy);
	i = 3;
	while (i < mrt->ix * mrt->iy * (mrt->bpp / 8))
	{
		// if (i * (mrt->bpp / 8) / (i) < BORDER)
		// {
		// 	i += (mrt->bpp / 8);
		// 	continue ;
		// }
		color[0] = mrt->addr[i + 3];
		color[1] = mrt->addr[i + 2];
		color[2] = mrt->addr[i + 1];
		fwrite(color, 1, 3, fp);
		i += (mrt->bpp / 8);
	}
	fclose(fp);
	write(1, "done\n", 5);
}

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

void	render_scene(t_mrt *mrt)
{
	set_all_cam_values(&mrt->cam, mrt->ix);
	if (mrt->first)
		write(1, "calculating pixel values... ", 28);
	pixel_calcul(mrt);
	if (mrt->first)
		write(1, "done\n", 5);
	if (mrt->save)
		write_to_ppm(mrt);
	if (!mrt->save)
	{
		mlx_clear_window(mrt->mlx, mrt->win);
		mlx_put_image_to_window(mrt->mlx, mrt->win, mrt->img, 0, 0);
		display_strings(mrt);
	}
	if (mrt->first)
		mrt->first = 0;
}

int	main(int ac, char **av)
{
	t_mrt	mrt;

	mrt.save = 0;
	if (ac != 2 && ac != 5)
		return (printf("Usage: ./miniRT <scene.rt>\n"), 1);
	if (ac == 5)
	{
		mrt.save = 1;
		if (ft_strcmp_1(av[2], "--save"))
			return (printf("Usage: ./miniRT <scene.rt> --save\n"), 1);
	}
	write(1, "initializing minirt... ", 23);
	if (init_minirt(&mrt, av, ac))
		return (1);
	write(1, "done\n", 5);
	mrt.first = 1;
	if (mrt.save)
		return (render_scene(&mrt), 0);
	render_scene(&mrt);
	ft_controls(&mrt);
	mlx_loop(mrt.mlx);
	return (0);
}
