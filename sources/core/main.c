/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:18:58 by ana               #+#    #+#             */
/*   Updated: 2023/03/27 00:38:31 by yridgway         ###   ########.fr       */
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
	int	i;

	i = 0;
	display_strings(mrt);
	set_all_cam_values(&mrt->cam);
	pixel_calcul(mrt);
	mlx_put_image_to_window(mrt->mlx, mrt->win, mrt->img, \
	((WX - IX) / 2) + BORDER, (WY - IY) / 2);
	while (i < mrt->obj_count[SPHERE])
	{
		if (mrt->sphere[i].option.bump_path)
		{
			mrt->sphere[i].option.bump_img = mlx_xpm_file_to_image(mrt->mlx, \
			mrt->sphere[i].option.bump_path, &mrt->sphere[i].option.bump_width, \
			&mrt->sphere[i].option.bump_height);
			mlx_put_image_to_window(mrt->mlx, mrt->win, \
			mrt->sphere[i].option.bump_img, 0, 0);
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	t_mrt	mrt;

	if (ac != 2)
		return (printf("Usage: ./miniRT <scene.rt>\n"), 1);
	if (init_minirt(&mrt, av[1]))
		return (1);
	render_scene(&mrt);
	ft_controls(&mrt);
	mlx_loop(mrt.mlx);
	return (0);
}
