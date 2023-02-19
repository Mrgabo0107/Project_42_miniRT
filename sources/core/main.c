/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:12:22 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/20 00:32:42 by yridgway         ###   ########.fr       */
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
	// printf("key: %d\n", key);
	if (key == 65307)
		end_mrt(mrt);
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
	// ft_printf_objects(&mrt);
	// print_pixels_coord(&mrt.cam);
	ft_controls(&mrt);
	mlx_loop(mrt.mlx);
	return (0);
}
