/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:51:49 by yridgway          #+#    #+#             */
/*   Updated: 2023/04/07 18:14:49 by gamoreno         ###   ########.fr       */
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
