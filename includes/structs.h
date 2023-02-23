/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:50:16 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/23 05:34:31 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "minirt.h"

# define UNDEFINED -1

typedef enum e_type
{
	AMBIENT,
	CAMERA,
	LIGHT,
	PLANE,
	SPHERE,
	CYLINDER,
	// SQUARE
}			t_type;

typedef struct s_vec
{
	double			x;
	double			y;
	double			z;
}			t_vec;

typedef struct s_base
{
	t_vec	bs_orig;
	t_vec	n1;
	t_vec	n2;
	t_vec	n3;
}		t_base;

/*----------------------------------------------------------------------------*/
/*									Camera									  */
/*----------------------------------------------------------------------------*/

// typedef struct s_ray
// {
// 	t_vec	origin;
// 	t_vec	direction;
// }			t_ray;

// typedef struct s_amblight
// {
// 	double	ratio;
// 	uint	color;
// }			t_amblight;

typedef struct s_cam
{
	t_vec	pos;
	t_vec	dir;
	double	fov;
	double	s_half_screen;
	double	w_h_ratio;
	double	step;
	t_base	screen_base;
}		t_cam;

typedef struct s_inter
{
	t_vec	pxl;
	int		type;
	int		index;
	double	dist;
	t_vec	inter_coor;
}			t_inter;

typedef struct s_discr
{
	double	b;
	double	a;
	double	c;
	double	dscr;
}		t_discr;

typedef struct s_cylval
{
	double	Ax;
	double	Ay;
	double	Az;
	double	Bx;
	double	By;
	double	Bz;
}		t_cylval;
/*----------------------------------------------------------------------------*/
/*									Objects									  */
/*----------------------------------------------------------------------------*/

typedef struct s_sphere
{
	t_vec	center;
	double	radius;
	uint	color;
}			t_sphere;

typedef struct s_plane
{
	t_vec	pos;
	t_vec	dir;
	uint	color;
}			t_plane;

typedef struct s_cylinder
{
	t_vec	pos;
	t_vec	dir;
	double	radius;
	double	height;
	uint	color;
}			t_cylinder;

typedef struct s_light
{
	t_vec	pos;
	double	ratio;
	uint	color;
	int		type;
}			t_light;

/*----------------------------------------------------------------------------*/
/*									Global									  */
/*----------------------------------------------------------------------------*/

typedef struct s_table
{
	char			*line[7];
	struct s_table	*next;
}			t_table;

typedef struct s_mem
{
	void			*ptr;
	struct s_mem	*next;
}	t_mem;

typedef struct s_mrt
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				endi;
	int				bpp;
	int				sizel;
	int				obj_count[6];
	t_light			amblight;
	t_cam			cam;
	t_light			light;
	t_sphere		*sphere;
	t_plane			*plane;
	t_cylinder		*cylinder;
}			t_mrt;

// typedef struct s_square
// {
// 	t_vec			center;
// 	t_vec			normal;
// 	double			side;
// }			t_square;

#endif