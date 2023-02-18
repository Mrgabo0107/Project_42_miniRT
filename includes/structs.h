/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ionorb <ionorb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:50:16 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/18 20:22:29 by ionorb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "minirt.h"

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	LIGHT,
	AMBIENT,
	CAMERA
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

typedef struct s_ray
{
	t_vec			origin;
	t_vec			direction;
}			t_ray;

typedef struct s_amblight
{
	double			ratio;
	t_vec			color;
}			t_amblight;

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

/*----------------------------------------------------------------------------*/
/*									Objects									  */
/*----------------------------------------------------------------------------*/

typedef struct s_sphere
{
	t_vec			center;
	double			radius;
}			t_sphere;

typedef struct s_plane
{
	t_vec			point;
	t_vec			normal;
}			t_plane;

typedef struct s_cylinder
{
	t_vec			center;
	t_vec			normal;
	double			diameter;
	double			height;
}			t_cylinder;

typedef struct s_light
{
	t_vec			origin;
	double			brightness;
	t_vec			color;
}			t_light;

/*----------------------------------------------------------------------------*/
/*									Global									  */
/*----------------------------------------------------------------------------*/

typedef union u_obj
{
	t_sphere		*sphere;
	t_plane			*plane;
	t_cylinder		*cylinder;
	t_light			*light;
	t_amblight		*amblight;
	t_cam			*cam;
	// t_square		*square;
}			t_obj;

typedef struct s_lst
{
	char			*line;
	t_obj			*obj;
	t_type			type;
	struct s_lst	*next;
}			t_lst;

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
	t_cam			cam;
	t_lst			*scene;
}			t_mrt;

// typedef struct s_square
// {
// 	t_vec			center;
// 	t_vec			normal;
// 	double			side;
// }			t_square;

#endif