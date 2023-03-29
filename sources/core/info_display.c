/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:23:17 by yridgway          #+#    #+#             */
/*   Updated: 2023/03/29 23:48:40 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*ft_get_index_str(int type, int index)
{
	char	*str;

	if (type == CAMERA)
		return (ft_strdup(""));
	str = ft_strjoin(ft_strdup(" "), ft_itoa(index + 1));
	return (str);
}

char	*ft_get_object_str(int type, int index)
{
	char	*str;
	char	*idx;

	str = ft_strdup("UNKNOWN");
	idx = ft_get_index_str(type, index);
	if (type == SPHERE)
		str = ft_strdup("SPHERE");
	if (type == PLANE)
		str = ft_strdup("PLANE");
	if (type == CYLINDER)
		str = ft_strdup("CYLINDER");
	if (type == CAMERA)
		str = ft_strdup("CAMERA");
	return (ft_strjoin(ft_strjoin("OBJECT: ", str), idx));
}

// void	set_background(t_mrt *mrt)
// {
// 	int		i[2];
// 	void	*img;
// 	char	*addr;
// 	int		bpp;
// 	int		sizel;
// 	int		endian;

// 	img = mlx_new_image(mrt->mlx, BORDER, IY);
// 	addr = mlx_get_data_addr(img, &bpp, &sizel, &endian);
// 	// addr = mlx_get_data_addr(img, NULL, NULL, NULL);
// 	i[0] = 0;
// 	while (i[0] < IY)
// 	{
// 		i[1] = 0;
// 		while (i[1] < BORDER)
// 		{
// 			*(unsigned int *)(addr + (i[0] * sizel + i[1] * (bpp / 8))) 
// 			= 0x00FF0000;
// 			i[1] += 1 + (i[0] % 2);
// 		}
// 		i[0]++;
// 	}
// 	mlx_put_image_to_window(mrt->mlx, mrt->win, img, 0, 0);
// 	mlx_destroy_image(mrt->mlx, img);
// }

void	display_strings(t_mrt *mrt)
{
	char	*object;
	char	*color;

	object = ft_get_object_str(mrt->curr_obj.type, mrt->curr_obj.index);
	color = ft_strjoin("color: ", ft_get_color_str(ft_get_obj_color(mrt, \
	mrt->curr_obj.type, mrt->curr_obj.index)));
	mlx_string_put(mrt->mlx, mrt->win, 10, 20, 0xFFFFFF, "---MiniRT---");
	mlx_string_put(mrt->mlx, mrt->win, 10, 40, 0xFFFFFF, "Controls:");
	mlx_string_put(mrt->mlx, mrt->win, 10, 60, 0xFFFFFF, "WASDQE - move cam");
	mlx_string_put(mrt->mlx, mrt->win, 10, 80, 0xFFFFFF, "Arrows - rotate cam");
	mlx_string_put(mrt->mlx, mrt->win, 10, 100, 0xFFFFFF, "ESC - exit");
	mlx_string_put(mrt->mlx, mrt->win, 10, 200, 0xFFFFFF, object);
	mlx_string_put(mrt->mlx, mrt->win, 10, 220, 0xFFFFFF, color);
}
