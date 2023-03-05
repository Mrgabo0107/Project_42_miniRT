/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 20:36:59 by ionorb            #+#    #+#             */
/*   Updated: 2023/03/04 14:39:25 by ana              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_print_sphere(t_sphere sphere)
{
	printf("\nSphere:\n");
	printf("Center: %f, %f, %f\n", sphere.center.x, sphere.center.y, sphere.center.z);
	printf("Radius: %f\n", sphere.radius);
	printf("Color: (%f,%f,%f)\n", sphere.color.r, sphere.color.g, sphere.color.b);
}

void	ft_print_plane(t_plane plane)
{
	printf("\nPlane:\n");
	printf("Center: %f, %f, %f\n", plane.pos.x, plane.pos.y, plane.pos.z);
	printf("Normal: %f, %f, %f\n", plane.dir.x, plane.dir.y, plane.dir.z);
	printf("Color: (%f,%f,%f)\n", plane.color.r, plane.color.g, plane.color.b);
}

void	ft_print_cylinder(t_cylinder cylinder)
{
	printf("\nCylinder:\n");
	printf("Center: %f, %f, %f\n", cylinder.pos.x, cylinder.pos.y, cylinder.pos.z);
	printf("Normal: %f, %f, %f\n", cylinder.dir.x, cylinder.dir.y, cylinder.dir.z);
	printf("Radius: %f\n", cylinder.radius);
	printf("Height: %f \n", cylinder.height);
	printf("Color: (%f,%f,%f)\n", cylinder.color.r, cylinder.color.g, cylinder.color.b);
}

void	ft_print_camera(t_cam cam)
{
	printf("\nCamera:\n");
	printf("Center: %f, %f, %f\n", cam.pos.x, cam.pos.y, cam.pos.z);
	printf("Normal: %f, %f, %f\n", cam.dir.x, cam.dir.y, cam.dir.z);
	printf("FOV: %f\n", cam.fov);
}

void	ft_print_light(t_light light)
{
	printf("\nLight:\n");
	printf("Center: %f, %f, %f\n", light.pos.x, light.pos.y, light.pos.z);
	printf("Brightness: %f\n", light.ratio);
	printf("Color: (%f,%f,%f)\n", light.color.r, light.color.g, light.color.b);
}

void	ft_print_ambient(t_light ambient)
{
	printf("\nAmbient:\n");
	printf("Brightness: %f\n", ambient.ratio);
	printf("Color: (%f,%f,%f)\n", ambient.color.r, ambient.color.g, ambient.color.b);
}

void	ft_printf_objects(t_mrt *mrt)
{
	ft_print_ambient(mrt->amblight);
	ft_print_camera(mrt->cam);
	ft_print_light(mrt->light);
	ft_print_plane(mrt->plane[0]);
	ft_print_sphere(mrt->sphere[0]);
	ft_print_cylinder(mrt->cylinder[0]);
	// i = 0;
	// while (sphere[i] != NULL)
	// 	ft_print_sphere(mrt->sphere[i++]);
	// i = 0;
	// while (mrt->plane[i])
	// 	ft_print_plane(mrt->plane[i++]);
	// i = 0;
	// while (mrt->cylinder[i])
	// 	ft_print_cylinder(mrt->cylinder[i++]);
}
