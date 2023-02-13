/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:51:33 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/13 18:16:37 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "../libs/minilibx-linux/mlx.h"
# include "../libs/libft/includes/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
// # include <fcntl.h>
# include <math.h>
# include <time.h>
# define WX 500
# define WY 500
# define IX 500
# define IY 500

typedef struct s_mrt
{
    void			*mlx;
	void			*win;
	void			*img;
    char            *addr;
	int				endi;
	int				bpp;
	int				sizel;
}			t_mrt;

#endif