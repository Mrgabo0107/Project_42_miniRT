/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:51:49 by yridgway          #+#    #+#             */
/*   Updated: 2023/04/07 13:10:32 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_init_mlx(t_mrt *mrt)
{
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
	mrt->curr_obj = define_curr_obj(CAMERA, 0);
	mrt->bounce = 0;
	mrt->num_objs = 9;
	mrt->ix = ix;
	mrt->iy = iy;
	if (ix <= 0)
		return ;
	mrt->obj_count = ft_calloc(mrt->num_objs, sizeof(int));
	mrt->threads = ft_malloc(sizeof(pthread_t) * THREADS);
	if (pthread_mutex_init(&mrt->mutex, NULL))
	{
		pthread_mutex_destroy(&mrt->mutex);
		ft_error("Failed to initialize mutex", NULL, NULL);
	}
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
	ft_free(mrt->cone);
	mrt->cone = NULL;
	ft_free(mrt->light);
	mrt->light = NULL;
	ft_free(mrt->triangle);
	mrt->triangle = NULL;
	while (i < mrt->num_objs)
		mrt->obj_count[i++] = 0;
	mrt->curr_obj = define_curr_obj(CAMERA, 0);
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
	mrt->mlx = mlx_init();
	ft_memory(mrt, SAVE_MLX);
	if (!mrt->mlx)
		return (ft_error("Problem initializing minilibx", NULL, NULL), 0);
	ft_parse(mrt);
	set_bump_maps(mrt);
	if (ft_init_mlx(mrt))
		return (printf("Problem initializing minilibx\n"), 1);
	return (0);
}
