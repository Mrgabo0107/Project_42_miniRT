/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:12:22 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/13 13:37:11 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int main(int ac, char **ag)
{
	t_mrt	mrt;

	(void)ac;
	(void)ag;
	mrt.mlx = mlx_init();
	if (mrt.mlx == NULL)
		return(1);
	mrt.win = mlx_new_window(mrt.mlx, WX, WY, "MiniRT");
	if (mrt.win == NULL)
		return(1);
	mlx_loop(mrt.mlx);
	return (0);
}