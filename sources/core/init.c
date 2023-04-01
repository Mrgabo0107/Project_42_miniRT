/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:51:49 by yridgway          #+#    #+#             */
/*   Updated: 2023/04/01 18:51:37 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_init_mlx(t_mrt *mrt)
{
	mrt->mlx = mlx_init();
	if (!mrt->mlx)
		return (ft_error("Problem initializing minilibx", NULL, NULL), 1);
	if (!mrt->save)
	{
		mrt->win = mlx_new_window(mrt->mlx, mrt->ix, mrt->iy, "MiniRT");
		if (!mrt->win)
			return (mlx_destroy_display(mrt->mlx), free(mrt->mlx), \
			ft_error("Problem initializing minilibx", NULL, NULL), 1);
	}
	mrt->img = mlx_new_image(mrt->mlx, mrt->ix, mrt->iy);
	if (!mrt->img)
		return (mlx_destroy_window(mrt->mlx, mrt->win), \
		mlx_destroy_display(mrt->mlx), free(mrt->mlx), \
		ft_error("Problem initializing minilibx", NULL, NULL), 1);
	mrt->addr = mlx_get_data_addr(mrt->img, &mrt->bpp, &mrt->sizel, &mrt->endi);
	if (!mrt->addr)
		return (ft_error("Problem initializing minilibx", NULL, NULL), 1);
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

void	ft_set_mrt(t_mrt *mrt, char *file, int ix, int iy)
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
	mrt->triangle = NULL;
	mrt->scene_path = file;
	c_obj.index = 0;
	c_obj.type = CAMERA;
	mrt->curr_obj = c_obj;
	mrt->bounce = 0;
	mrt->num_objs = 9;
	mrt->obj_count = ft_malloc(mrt->num_objs * sizeof(int));
	mrt->ix = ix;
	mrt->iy = iy;
	mrt->threads = ft_malloc(sizeof(pthread_t) * THREADS);
	pthread_mutex_init(&mrt->mutex, NULL);
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
	mrt->curr_obj.index = 0;
	mrt->curr_obj.type = CAMERA;
	ft_parse(mrt);
	set_bump_maps(mrt);
}

int	init_minirt(t_mrt *mrt, char **av, int ac)
{
	(void)ac;
	if (mrt->save)
		ft_set_mrt(mrt, av[1], ft_atoi(av[3]), ft_atoi(av[4]));
	else
		ft_set_mrt(mrt, av[1], IX, IY);
	ft_parse(mrt);
	if (ft_init_mlx(mrt))
		return (printf("Problem initializing minilibx\n"), 1);
	set_bump_maps(mrt);
	return (0);
}
