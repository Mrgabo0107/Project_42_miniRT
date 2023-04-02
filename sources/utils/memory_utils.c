/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel <yoel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 01:36:18 by ionorb            #+#    #+#             */
/*   Updated: 2023/04/02 20:21:27 by yoel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_save_mlx(void *ptr, void **mlx, void **win, void **img)
{
	t_mrt	*mrt;

	mrt = (t_mrt *)(ptr);
	*mlx = mrt->mlx;
	*win = mrt->win;
	*img = mrt->img;
}

void	ft_free_mlx(void **mlx, void **win, void **img)
{
	if (*img)
		mlx_destroy_image(*mlx, *img);
	if (*win)
		mlx_destroy_window(*mlx, *win);
	if (*mlx)
	{
		mlx_destroy_display(*mlx);
		free(*mlx);
	}
}

void	ft_free_one(t_mem *mem, void *thing)
{
	t_mem	*prev;
	t_mem	*after;

	prev = mem;
	if (mem)
		mem = mem->next;
	while (mem && mem->next)
	{
		after = mem->next;
		if (mem->ptr == thing)
		{
			free(mem->ptr);
			free(mem);
			mem = after;
			prev->next = after;
		}
		prev = mem;
		mem = mem->next;
	}
}

int	mem_size(t_mem *mem)
{
	int	i;

	i = 0;
	while (mem)
	{
		i++;
		mem = mem->next;
	}
	return (i);
}
