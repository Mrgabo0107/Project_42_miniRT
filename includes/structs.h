/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:50:16 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/15 17:27:32 by yridgway         ###   ########.fr       */
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
	t_vec			origin;
	t_vec			direction;
	double			fov;
}			t_cam;

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
	// t_square		*square;
}			t_obj;

typedef struct s_lst
{
	t_obj			*content;
	t_type			type;
	struct s_lst	*next;
}			t_lst;

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
	t_lst			*scene;
}			t_mrt;

// typedef struct s_square
// {
// 	t_vec			center;
// 	t_vec			normal;
// 	double			side;
// }			t_square;

#endif