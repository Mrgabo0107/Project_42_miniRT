/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:51:49 by yridgway          #+#    #+#             */
/*   Updated: 2023/03/27 20:47:06 by yridgway         ###   ########.fr       */
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

int	valid_rt_file(char *file, int fd)
{
	int	size;

	if (!file || !*file)
		return (0);
	size = ft_strlen(file);
	if (size < 3)
		return (0);
	if (file[size - 1] != 't' || file[size - 2] != 'r' || file[size - 3] != '.')
		return (0);
	if (read(fd, NULL, 0) < 0)
		ft_error("Failed to read file", file, strerror(errno));
	return (1);
}

void	ft_set_mrt(t_mrt *mrt, char *file)
{
	t_curr_ob	c_obj;
	int			i;

	i = 0;
	mrt->mlx = NULL;
	mrt->win = NULL;
	mrt->img = NULL;
	mrt->addr = NULL;
	mrt->sphere = NULL;
	mrt->plane = NULL;
	mrt->cylinder = NULL;
	mrt->cone = NULL;
	mrt->light = NULL;
	mrt->scene_path = file;
	c_obj.index = 0;
	c_obj.type = CAMERA;
	mrt->curr_obj = c_obj;
	mrt->bounce = 0;
	mrt->num_objs = 8;
	mrt->obj_count = ft_malloc(mrt->num_objs * sizeof(int));
	while (i < mrt->num_objs)
		mrt->obj_count[i++] = 0;
}

void	ft_reinit(t_mrt *mrt)
{
	int	i;

	i = 0;
	ft_free(mrt->sphere);
	mrt->sphere = NULL;
	ft_free(mrt->plane);
	mrt->plane = NULL;
	ft_free(mrt->cylinder);
	mrt->cylinder = NULL;
	while (i < mrt->num_objs)
		mrt->obj_count[i++] = 0;
	ft_parse(mrt);
}

int	init_minirt(t_mrt *mrt, char *file)
{
	ft_set_mrt(mrt, file);
	ft_parse(mrt);
	if (ft_init_mlx(mrt))
		return (printf("Problem initializing minilibx\n"), 1);
	return (0);
}
