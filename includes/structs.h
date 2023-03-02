/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:50:16 by yridgway          #+#    #+#             */
/*   Updated: 2023/0 by gamoreno         ###   ########.fr       */
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

typedef	struct s_mtrx
{
	t_vec	r1;
	t_vec	r2;
	t_vec	r3;
}	t_mtrx;


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

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}			t_rgb;
typedef struct s_inter
{
	int		type;
	int		index;
	double	dist;
	t_vec	inter_coor;
	t_vec	norm;
	t_rgb	color;
}			t_inter;

typedef struct s_discr
{
	double	b;
	double	a;
	double	c;
	double	dscr;
}		t_discr;

/*----------------------------------------------------------------------------*/
/*									Objects									  */
/*----------------------------------------------------------------------------*/

typedef struct s_sphere
{
	t_vec	center;
	double	radius;
	t_rgb	color;
}			t_sphere;

typedef struct s_plane
{
	t_vec	pos;
	t_vec	dir;
	t_rgb	color;
}			t_plane;

typedef struct s_cylinder
{
	t_vec	pos;
	t_vec	dir;
	t_vec	top;
	t_vec	bottom;
	double	radius;
	double	height;
	t_rgb	color;
	t_base	base;
}			t_cylinder;

typedef struct s_light
{
	t_vec	pos;
	double	ratio;
	t_rgb	color;
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