/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 01:36:18 by ionorb            #+#    #+#             */
/*   Updated: 2023/04/05 03:30:48 by yridgway         ###   ########.fr       */
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

int	ft_free_one(t_mem *mem, void *thing)
{
	t_mem	*prev;
	t_mem	*after;

	if (!mem || !thing)
		return (0);
	prev = mem;
	if (mem)
		mem = mem->next;
	while (mem && mem->next)
	{
		after = mem->next;
		if (mem->ptr == thing || !mem->ptr)
		{
			free(mem->ptr);
			free(mem);
			mem = after;
			prev->next = after;
		}
		prev = mem;
		mem = mem->next;
	}
	if (mem && mem->ptr == thing)
		return (free(mem->ptr), free(mem), prev->next = NULL, 0);
	return (0);
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
