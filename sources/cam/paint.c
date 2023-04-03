/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel <yoel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 22:24:35 by gamoreno          #+#    #+#             */
/*   Updated: 2023/04/02 19:13:48 by yoel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	my_mlx_pixel_put(t_mrt *mrt, int x, int y, int color)
{
	char	*dst;

	if (!mrt->save && x < BORDER)
		color = diminish_color(color, 0.3);
	dst = mrt->addr + (y * mrt->sizel + x * (mrt->bpp / 8));
	*(unsigned int *)dst = color;
}

void	*ft_paint(void *data)
{
	t_mrt	*mrt;
	int		i;
	int		j;
	int		color;

	mrt = (t_mrt *)data;
	i = 0;
	while (i < mrt->ix)
	{
		j = 0;
		ft_percentage_bar(mrt);
		while (j < mrt->iy - 1)
		{
			if (j % THREADS == mrt->i)
			{
				color = get_pixel_color(mrt, i + 1, j + 1);
				my_mlx_pixel_put(mrt, i, j, color);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

void	pixel_calcul(t_mrt *mrt)
{
	int		i;
	t_mrt	*dat;

	i = 0;
	mrt->i = 0;
	dat = ft_copy_mrt(mrt, THREADS);
	while (i < THREADS)
	{
		dat[i].i = i;
		pthread_create(&mrt->threads[i], NULL, \
		(void *)ft_paint, (void *)&dat[i]);
		i++;
	}
	i = 0;
	while (i < THREADS)
	{
		pthread_join(mrt->threads[i], NULL);
		i++;
	}
	if (mrt->first)
		printf("\r[100%%]\n");
	ft_free_mrt(dat, THREADS);
}
