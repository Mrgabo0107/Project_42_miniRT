/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel <yoel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:51:33 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/17 21:03:00 by yoel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "libft.h"
# include "structs.h"
# include "define.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include <sys/types.h>
# include <limits.h>
# include <errno.h>
# include <string.h>

//init
int			init_minirt(t_mrt *mrt, char *file);
int			ft_init_mlx(t_mrt *mrt);
void		ft_reinit(t_mrt *mrt);
int			valid_rt_file(char *file, int fd);

//end
int			end_mrt(t_mrt *mrt);

//parsing
int			ft_parse(t_mrt *mrt);
int			ft_strcmp_1(char *s1, char *s2);
int			eval_obj(char *line);
t_table		*ft_fill_table(int fd);
int			ft_arg_count(char **line);
void		ft_error(char *msg, char *extra, char *extra2);

//cell filling
double		ft_fill_ratio(char *cell);
t_rgb		ft_fill_rgb(char *cell);
t_vec		ft_fill_pos(char *cell, int dir);
double		ft_fill_size(char *cell, int fov);
void		ft_check_dots_and_minus(char *str);
int			check_valid_number(char *str);
void		valid_nums(char **line);
int			check_for_chars(char *str, char *cell);
int			out_of_range(double num, double min, double max);

//fill objects
t_cam		ft_fill_cam(char *line[7]);
t_light		ft_fill_light(char *line[7], int amb);
t_sphere	ft_fill_sphere(char *line[7]);
t_plane		ft_fill_plane(char *line[7]);
t_cylinder	ft_fill_cylinder(char *line[7]);

//utils
char		*get_next_line(int fd);

//list
// t_lst		*ft_lstnew(void *obj, int type);
// t_lst		*ft_lstadd_back(t_lst *lst, t_lst *new);
// t_lst		*ft_lstadd_new(t_lst *lst, void *obj, int type);
t_table		*ft_tablenew(char **line);
t_table		*ft_tableadd_back(t_table *table, t_table *new);
t_table		*ft_tableadd_new(t_table *table, char **line);

//memory
void		*ft_malloc(long long int size);
void		*ft_memory(void *ptr, long long int size);
void		ft_free(void *ptr);
void		ft_free_one(t_mem *mem, void *thing);
void		ft_quit(int status);
void		clean_memory(void);
void		ft_add_to_mem(void *thing);
void		ft_close(int fd);
void		ft_close_fd(int *fd);
void		ft_save_mlx(void *ptr, void **mlx, void **win, void **img);
void		ft_free_mlx(void **mlx, void **win, void **img);

//free
void		ft_free_array(char **array);
void		ft_free_table(t_table *table);

//math
double		int_pow(double basis, int exp);
double		vect_norm(t_vec v);
t_vec		fill_coord(double c1, double c2, double c3);
t_vec		normalize(t_vec v);
t_vec		scal_vec(double scalar, t_vec vector);
t_vec		vec_sum(t_vec v1, t_vec v2);
double		rad_and_deg(double angle, int ctrl);
void		print_vector(t_vec v); //debug
double		min_v(double d1, double d2);
double		max_v(double d1, double d2);
double		v_abs(double x);
double		dot_prod(t_vec v1, t_vec v2);
t_vec		cross_prod(t_vec v1, t_vec v2);
double		vect_norm(t_vec v);
t_vec		vec_rest(t_vec v1, t_vec v2);
double		norm_raised_2(t_vec v);
t_base		get_obj_base(t_vec	dir);
t_vec		mtrx_by_vec(t_mtrx m, t_vec v);
double		mtrx_det(t_mtrx m);
t_mtrx		mtrx_trsp(t_mtrx m);
t_mtrx		mtrx_adj(t_mtrx m);
t_mtrx		scal_mtrx(double s, t_mtrx m);
t_mtrx		invert_mtrx(t_mtrx m);
double		perp_to_plane(t_vec point, t_vec plane_pos, t_vec plane_norm);
double		ft_max_valid(double a, double b);
t_mtrx		fill_mtrx(t_vec v1, t_vec v2, t_vec v3);
t_mtrx		init_base_mtrx(t_base *base);
double		solve_quad(t_discr *info);
double		decimal_part(double n);
t_mtrx		define_rot_mtrx(t_vec rot_axis, double sin, double cos);
t_base		general_rotation(t_base base, int ctrl, double rad);

//plane
t_vec		get_normal_plane(t_mrt *mrt, t_inter inter);
void		check_planes(t_mrt *mrt, t_inter *ctrl, t_vec point, t_vec dir);
double		distance_to_plane(t_vec start_point,
				t_vec plane_pos, t_vec plane_dir, t_vec ray);

//sphere
t_vec		get_normal_sphere(t_mrt *mrt, t_inter inter);
void		check_spheres(t_mrt *mrt, t_inter *ctrl, t_vec point, t_vec dir);
t_discr		get_sph_dscr(t_vec ncam, t_vec dir, double square_rad);

//cylinder
t_vec		get_normal_cylinder(t_mrt *mrt, t_inter inter);
void		check_cylinders(t_mrt *mrt, t_inter *ctrl, t_vec point, t_vec dir);
int			cam_in_cyl(t_mrt *mrt, int indx, t_vec new_cam);
t_rgb		print_cyl_color(t_mrt *mrt, int index);
t_cyl_ctrl	get_dist_to_cyl(t_cylinder cyl, t_vec new_cam, t_vec new_dirc);
t_discr		get_cyl_disc(t_cylinder cyl, t_vec new_cam, t_vec new_dirc);

//camera
t_inter		check_intersections(t_mrt *mrt, t_vec point, t_vec dir);
void		set_all_cam_values(t_cam *cam);
t_vec		screen_pxl_by_indx(t_cam *cam, int i, int j);
void		my_mlx_pixel_put(t_mrt *mrt, int x, int y, int color);
void		pixel_calcul(t_mrt *mrt);
int			get_pixel_color(t_mrt *mrt, int x, int y);
double		distance_to_cap(t_vec start_pos, t_cylinder cylinder, t_vec ray);
t_inter		fill_ctrl(t_mrt *mrt, int type, int index, double dist);
t_rgb		chosen_obj(t_mrt *mrt, int x, int y, t_rgb color);
t_vec		get_normal_at_point(t_mrt *mrt, t_inter inter);

//color
t_rgb		get_color(t_mrt *mrt, t_inter *ctr, t_vec dir);
t_rgb		ft_make_rgb(int r, int g, int b);
t_rgb		ft_make_rgb_ratio(t_rgb color);
t_rgb		normalize_color(t_rgb color);
t_rgb		show_light_sources(t_mrt *mrt, t_rgb color, t_vec dir);
t_rgb		get_opposite_color(t_rgb color);
double		get_angle_between(t_vec v1, t_vec v2);
t_rgb		add_ambient(t_rgb color, t_rgb ctr, t_light amb);
t_rgb		add_diffuse(t_inter *ctr, t_rgb color, t_vec to_light, \
t_light light);
t_rgb		add_specular(t_inter *ctr, t_rgb color, t_vec h, t_light light);
t_inter		check_shaddow(t_mrt *mrt, t_inter *ctr, t_vec dir, double len);

//hooks_management
int			key_press(int key, t_mrt *mrt);
int			mouse_press(int button, int x, int y, t_mrt *mrt);
void		move_obj(t_mrt *mrt, int key);
void		rotate_obj(t_mrt *mrt, int key);

#endif