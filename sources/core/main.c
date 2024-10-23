/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:18:58 by ana               #+#    #+#             */
/*   Updated: 2023/04/08 12:26:20 by gamoreno         ###   ########.fr       */
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

void	render_scene(t_mrt *mrt)
{
	set_all_cam_values(&mrt->cam, mrt->ix);
	if (mrt->first)
		write(1, "calculating pixel values...\n", 29);
	pixel_calcul(mrt);
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

int	ft_save_parsing(char **av)
{
	if (ft_strcmp_1(av[2], "--save"))
		return (printf("Usage: ./miniRT <scene.rt> --save\n"), 1);
	if (ft_atoi(av[3]) < 1 || ft_atoi(av[4]) < 1 || ft_strlen(av[3]) > 6 \
	|| ft_strlen(av[4]) > 6 || ft_atoi(av[3]) > 10000 \
	|| ft_atoi(av[4]) > 10000)
		return (printf("Please enter a save resolution between 20 and 10000\n"), \
		1);
	return (0);
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
		if (ft_save_parsing(av))
			return (1);
	}
	write(1, "initializing minirt... ", 23);
	if (init_minirt(&mrt, av, ac))
		return (1);
	write(1, "done\n", 5);
	mrt.first = 1;
	if (mrt.save)
		return (render_scene(&mrt), ft_quit(EXIT_OK), 0);
	render_scene(&mrt);
	ft_controls(&mrt);
	mlx_loop(mrt.mlx);
	return (0);
}
