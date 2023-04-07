/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_bump_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:04:14 by yridgway          #+#    #+#             */
/*   Updated: 2023/04/07 18:19:02 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	bump_to_array(t_bump *bump_map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	bump_map->array = ft_malloc(bump_map->height * sizeof(int *));
	while (i < bump_map->height)
	{
		bump_map->array[i] = ft_malloc(bump_map->width * sizeof(int));
		i++;
	}
	i = 0;
	while (i < bump_map->height)
	{
		while (j < bump_map->width)
		{
			bump_map->array[i][j] = \
			*(unsigned int *)(bump_map->addr + \
			(i * bump_map->sizel + j * (bump_map->bpp / 8)));
			j++;
		}
		j = 0;
		i++;
	}
}
