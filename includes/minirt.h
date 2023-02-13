/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:51:33 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/13 13:31:59 by gamoreno         ###   ########.fr       */
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
    char            *mot;
	int				endian;
	int				bpp;
	int				sizel;
}			t_mrt;

#endif