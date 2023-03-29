/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:18:58 by ana               #+#    #+#             */
/*   Updated: 2023/03/29 23:48:10 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	write_to_ppm(t_mrt *mrt)
{
	int		i;
	int		fd;
	char	*line;

	fd = open("bump.ppm", O_CREAT | O_RDWR, 0777);
	line = ft_strdup("P6\n");
	line = ft_strjoin(line, ft_strjoin(ft_itoa(mrt->ix), \
	ft_strjoin(" ", ft_itoa(mrt->iy))));
	line = ft_strjoin(line, "\n255\n");
	write(fd, line, ft_strlen(line));
	ft_free(line);
	i = 0;
	while (i < mrt->ix * mrt->iy * (mrt->bpp / 8))
	{
		write(fd, mrt->addr + i, 1);
		i++;
		if ((i + 1) % 4 == 0)
			i++;
	}
	close(fd);
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
	pixel_calcul(mrt);
	if (mrt->save)
		write_to_ppm(mrt);
	mlx_clear_window(mrt->mlx, mrt->win);
	if (!mrt->save)
		mlx_put_image_to_window(mrt->mlx, mrt->win, mrt->img, 0, 0);
	if (!mrt->save)
		display_strings(mrt);
}

int	main(int ac, char **av)
{
	t_mrt	mrt;

	if (ac != 2 && ac != 5)
		return (printf("Usage: ./miniRT <scene.rt>\n"), 1);
	if (init_minirt(&mrt, av, ac))
		return (1);
	if (ac == 5)
	{
		if (ft_strcmp_1(av[2], "--save"))
			return (printf("Usage: ./miniRT <scene.rt> --save\n"), 1);
		mrt.ix = ft_atoi(av[3]);
		mrt.iy = ft_atoi(av[4]);
		mrt.save = 1;
		return (render_scene(&mrt), 0);
	}
	render_scene(&mrt);
	ft_controls(&mrt);
	mlx_loop(mrt.mlx);
	return (0);
}
