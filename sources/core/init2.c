/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:51:49 by yridgway          #+#    #+#             */
/*   Updated: 2023/04/08 12:18:49 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_some_mrt_values(t_mrt *mrt, char *file)
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
}

void	ft_set_mrt(t_mrt *mrt, char *file, int ix, int iy)
{
	init_some_mrt_values(mrt, file);
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
	mrt->mutexs = &mrt->mutex;
}

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
		color[0] = mrt->addr[i + 3];
		color[1] = mrt->addr[i + 2];
		color[2] = mrt->addr[i + 1];
		fwrite(color, 1, 3, fp);
		i += (mrt->bpp / 8);
	}
	fclose(fp);
	write(1, "done\n", 5);
}
