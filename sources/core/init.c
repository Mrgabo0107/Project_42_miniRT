/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:51:49 by yridgway          #+#    #+#             */
/*   Updated: 2023/03/04 02:16:04 by ana              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_init_mlx(t_mrt *mrt)
{
	mrt->mlx = mlx_init();
	if (!mrt->mlx)
		return (1);
	mrt->win = mlx_new_window(mrt->mlx, WX, WY, "MiniRT");
	if (!mrt->win)
		return (mlx_destroy_display(mrt->mlx), free(mrt->mlx), 1);
	mrt->img = mlx_new_image(mrt->mlx, IX, IY);
	if (!mrt->img)
		return (mlx_destroy_window(mrt->mlx, mrt->win), \
		mlx_destroy_display(mrt->mlx), free(mrt->mlx), 1);
	mrt->addr = mlx_get_data_addr(mrt->img, &mrt->bpp, &mrt->sizel, &mrt->endi);
	if (!mrt->addr)
		return (end_mrt(mrt), 1);
	ft_memory(mrt, SAVE_MLX);
	return (0);
}

int	valid_rt_file(char *file)
{
	int	size;

	if (!file || !*file)
		return (0);
	size = ft_strlen(file);
	if (size < 3)
		return (0);
	if (file[size - 1] != 't' || file[size - 2] != 'r' || file[size - 3] != '.')
		return (0);
	return (1);
}

void	ft_set_zero(t_mrt *mrt)
{
	mrt->mlx = NULL;
	mrt->win = NULL;
	mrt->img = NULL;
	mrt->addr = NULL;
	mrt->sphere = NULL;
	mrt->plane = NULL;
	mrt->cylinder = NULL;
}

int	init_minirt(t_mrt *mrt, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0 || !valid_rt_file(file))
		ft_error(FILE_ERROR, file, FILE_INSTRUCTIONS);
	ft_set_zero(mrt);
	ft_parse(mrt, fd);
	if (ft_init_mlx(mrt))
		return (printf("Problem initializing minilibx\n"), 1);
	return (0);
}
