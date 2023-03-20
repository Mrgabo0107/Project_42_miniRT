/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:18:58 by ana               #+#    #+#             */
/*   Updated: 2023/03/20 20:05:53 by yridgway         ###   ########.fr       */
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

char	*ft_get_type_str(int type)
{
	if (type == SPHERE)
		return ("SPHERE");
	if (type == PLANE)
		return ("PLANE");
	if (type == CYLINDER)
		return ("CYLINDER");
	if (type == CAMERA)
		return ("CAMERA");
	return ("UNKNOWN");
}

void	display_strings(t_mrt *mrt)
{
	mlx_string_put(mrt->mlx, mrt->win, 10, 20, 0xFFFFFF, "MiniRT");
	mlx_string_put(mrt->mlx, mrt->win, 10, 40, 0xFFFFFF, "Controls:");
	mlx_string_put(mrt->mlx, mrt->win, 10, 60, 0xFFFFFF, "WASDQE - move");
	mlx_string_put(mrt->mlx, mrt->win, 10, 80, 0xFFFFFF, "Arrows - rotate");
	mlx_string_put(mrt->mlx, mrt->win, 10, 100, 0xFFFFFF, "Scroll - zoom");
	mlx_string_put(mrt->mlx, mrt->win, 10, 120, 0xFFFFFF, "ESC - exit");
	mlx_string_put(mrt->mlx, mrt->win, 10, 200, 0xFFFFFF, ft_strjoin("OBJECT: ", ft_get_type_str(mrt->curr_obj.type)));
	// mlx_string_replace(mrt->mlx, mrt->win, 10, 220, 0xFFFFFF, ft_strjoin("INDEX: ", ft_itoa(mrt->curr_obj.index)));
}

void	render_scene(t_mrt *mrt)
{
	display_strings(mrt);
	set_all_cam_values(&mrt->cam);
	pixel_calcul(mrt);
	mlx_put_image_to_window(mrt->mlx, mrt->win, mrt->img, \
	((WX - IX) / 2) + BORDER, (WY - IY) / 2);
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
