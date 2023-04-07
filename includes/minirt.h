/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:51:33 by gamoreno          #+#    #+#             */
/*   Updated: 2023/04/07 16:42:03 by yridgway         ###   ########.fr       */
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
# include <time.h>
# include <pthread.h>

//init
int			init_minirt(t_mrt *mrt, char **av, int ac);
int			ft_init_mlx(t_mrt *mrt);
void		ft_reinit(t_mrt *mrt);
int			valid_rt_file(char *file, int fd);
void		ft_set_mrt(t_mrt *mrt, char *file, int ix, int iy);
void		bump_to_array(t_bump *bump_map);

//end
int			end_mrt(t_mrt *mrt);

//parsing
int			ft_parse(t_mrt *mrt);
int			ft_strcmp_1(char *s1, char *s2);
int			eval_obj(char *line);
t_table		*ft_fill_table(int fd, int num_objs);
int			ft_arg_count(char **line);
void		ft_error(char *msg, char *extra, char *extra2);
t_option	ft_fill_options(t_mrt *mrt, t_table *table, t_rgb color);
int			eval_option(char *line);
int			*int_arrcpy(int *arr, int size);
void		ft_allocate_objs(t_mrt *mrt, int *count);

//eval objects
int			ft_strcmp_1(char *s1, char *s2);
int			eval_option(char *line);
int			eval_obj(char *line);

//cell filling
double		ft_fill_ratio(char *cell);
t_rgb		ft_fill_rgb(char *cell);
t_vec		ft_fill_pos(char *cell, int dir);
double		ft_fill_size(char *cell, int fov);
char		*ft_fill_xpm(char *cell);
void		ft_check_dots_and_minus(char *str);
int			check_valid_number(char *str);
void		valid_nums(char **line);
int			check_for_chars(char *str, char *cell);
int			out_of_range(double num, double min, double max);

//fill objects
t_cam		ft_fill_cam(t_table *table, char **line);
t_light		ft_fill_light(t_table *table, char **line, int amb);
t_sphere	ft_fill_sphere(t_mrt *mrt, t_table *table, char **line);
t_plane		ft_fill_plane(t_mrt *mrt, t_table *table, char **line);
t_cylinder	ft_fill_cylinder(t_mrt *mrt, t_table *table, char **line);
t_cone		ft_fill_cone(t_mrt *mrt, t_table *table, char **line);
t_triangle	ft_fill_triangle(t_mrt *mrt, t_table *table, char **line);

//utils
char		*get_next_line(int fd);
char		*ft_strjoin_free(char	*s1, char *s2);

//list
t_table		*ft_tablenew(char **line, int num_objs);
t_table		*ft_tableadd_back(t_table *table, t_table *new);
t_table		*ft_tableadd_new(t_table *table, char **line, int num_objs);
int			mem_size(t_mem *mem);

//memory
void		*ft_malloc(long long int size);
void		*ft_memory(void *ptr, long long int size);
void		ft_free(void *ptr);
int			ft_free_one(t_mem *mem, void *thing);
void		ft_quit(int status);
void		clean_memory(void);
void		ft_add_to_mem(void *thing);
void		ft_close(int fd);
void		ft_close_fd(int *fd);
void		ft_save_mlx(void *ptr, void **mlx, void **win, void **img);
void		ft_free_mlx(void **mlx, void **win, void **img);
void		ft_get_mem_size(void);

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
double		integer_part(double n);
t_vec		get_spheric_coord(t_vec orig);
t_vec		get_cyl_coor(t_vec orig);
int			i_min_v(int a, int b);

//plane
t_vec		get_normal_plane(t_mrt *mrt, t_inter inter);
void		check_planes(t_mrt *mrt, t_inter *ctrl, t_vec point, t_vec dir);
double		distance_to_plane(t_vec start_point,
				t_vec plane_pos, t_vec plane_dir, t_vec ray);
t_rgb		get_plane_color(t_mrt *mrt, int index, t_vec intrsc);
t_vec		plane_bumped(t_mrt *mrt, t_inter inter, t_vec without);
t_rgb		get_plane_texture(t_mrt *mrt, t_inter inter);

//triangle
t_vec		get_normal_triangle(t_mrt *mrt, t_inter inter);
double		distance_to_triangle(t_vec start_point, t_triangle tri, t_vec ray);
void		check_triangles(t_mrt *mrt, t_inter *ctrl, t_vec point, t_vec dir);

//sphere
t_vec		get_normal_sphere(t_mrt *mrt, t_inter inter);
void		check_spheres(t_mrt *mrt, t_inter *ctrl, t_vec point, t_vec dir);
t_discr		get_sph_dscr(t_vec ncam, t_vec dir, double square_rad);
t_rgb		get_sphere_color(t_mrt *mrt, int index, t_vec intrsc);
t_vec		sphere_bumped(t_mrt *mrt, t_inter inter, t_vec without);

//cylinder
t_vec		get_normal_cylinder(t_mrt *mrt, t_inter inter);
void		check_cylinders(t_mrt *mrt, t_inter *ctrl, t_vec point, t_vec dir);
int			cam_in_cyl(t_mrt *mrt, int indx, t_vec new_cam);
t_rgb		print_cyl_color(t_mrt *mrt, int index);
t_cuad_ctr	get_dist_to_cyl(t_cylinder cyl, t_vec new_cam, t_vec new_dirc);
t_discr		get_cyl_disc(t_cylinder cyl, t_vec new_cam, t_vec new_dirc);
t_rgb		get_cyl_color(t_mrt *mrt, int index, t_vec intrsc, t_cuad_ctr ctr);
t_vec		cyl_normal_from_map(t_mrt *mrt, t_inter i, \
			t_vec c_cr, t_vec cyl_cr);
double		get_angular_resol(t_mrt *mrt, t_inter inter, double r_c, int width);
double		get_body_resol(t_mrt *mrt, t_inter inter, double r_c, int height);
t_rgb		get_cyl_texture(t_mrt *mrt, t_inter inter);

//cone
void		check_cones(t_mrt *mrt, t_inter *ctrl, t_vec point, t_vec dir);
int			cam_in_cone(t_mrt *mrt, int indx, t_vec n_c, double tan);
t_vec		get_normal_cone(t_mrt *mrt, t_inter inter);
void		move_cone(t_mrt *mrt, int key);
double		solve_cone_quad(t_discr *info, t_vec *f_n);
t_rgb		check_cone_contour(t_mrt *mrt, t_vec curr_dir, t_rgb color);
t_cuad_ctr	get_dist_to_cone(t_cone cone, t_vec n_c, t_vec n_d, double tang);
int			contour_cone(t_mrt *mrt, t_vec *new, double c, double tang);
t_discr		get_cone_disc(t_vec *f_n, double tan);
void		fov_ctr(t_mrt *mrt, int key);
t_rgb		get_cone_color(t_mrt *mrt, int i, t_vec *new, t_cuad_ctr ctr);
t_vec		cone_nml_frm_map(t_mrt *mrt, t_inter itr, t_vec c_cr, t_vec cyl_cr);
t_vec		cone_bumped(t_mrt *mrt, t_inter inter, t_vec without);


//camera
t_inter		check_intersections(t_mrt *mrt, t_vec point, t_vec dir);
void		set_all_cam_values(t_cam *cam, int ix);
t_vec		screen_pxl_by_indx(t_mrt *mrt, t_cam *cam, int i, int j);
void		my_mlx_pixel_put(t_mrt *mrt, int x, int y, int color);
void		pixel_calcul(t_mrt *mrt);
int			get_pixel_color(t_mrt *mrt, int x, int y);
double		distance_to_cap(t_vec start_pos, t_cylinder cylinder, t_vec ray);
t_inter		fill_ctrl(t_mrt *mrt, int type, int index, double dist);
t_rgb		chosen_obj(t_mrt *mrt, int x, int y, t_rgb color);
t_vec		get_normal_at_point(t_mrt *mrt, t_inter inter);
t_mrt		*ft_copy_mrt(t_mrt *mrt, int num);
void		ft_percentage_bar(t_mrt *mrt);
void		ft_free_mrt(t_mrt *mrt, int num);

//color
// t_rgb		get_color(t_mrt *mrt, t_inter *ctr, t_vec dir);
t_rgb		ft_make_rgb(int r, int g, int b);
t_rgb		ft_make_rgb_ratio(t_rgb color);
t_rgb		normalize_color(t_rgb color);
t_rgb		show_light_sources(t_mrt *mrt, t_rgb color, t_vec dir);
t_rgb		get_opposite_color(t_rgb color);
// double		get_angle_between(t_vec v1, t_vec v2);
t_rgb		get_ambient(t_rgb ctr, t_light amb, double mirror);
t_rgb		get_reflection(t_mrt *mrt, t_inter *ctr, t_vec dir);
t_rgb		get_diffuse(t_inter *ctr, t_vec to_light, \
t_light light);
t_rgb		get_specular(t_inter *ctr, t_vec pos, t_vec to_light, \
t_light light);
t_rgb		mult_color(t_rgb color, double mult);
t_rgb		add_color(t_rgb color1, t_rgb color2);
t_inter		check_shaddow(t_mrt *mrt, t_inter *ctr, t_vec dir, double len);
t_rgb		get_radiance(t_mrt *mrt, t_inter *ctr, t_light light);
t_rgb		apply_lighting(t_mrt *mrt, t_inter *ctr, t_vec dir, t_rgb color);
int			diminish_color(int color, double percent);
t_rgb		convert_to_rgb(int color);

//hooks_management
int			key_press(int key, t_mrt *mrt);
int			mouse_press(int button, int x, int y, t_mrt *mrt);
void		move_obj(t_mrt *mrt, int key);
void		rotate_obj(t_mrt *mrt, int key);
void		render_scene(t_mrt *mrt);
void		chg_options(t_mrt *mrt, int key);
void		radius_ctr(t_mrt *mrt, int key);
void		height_ctr(t_mrt *mrt, int key);
void		bump_option(t_mrt *mrt, int key);
void		chess_ctr(t_mrt *mrt, int key);
void		cam_ctr(t_mrt *mrt, int key);
t_curr_ob	define_curr_obj(int type, int index);

//info display
void		display_strings(t_mrt *mrt);
t_rgb		ft_get_obj_color(t_mrt *mrt, int type, int index);
char		*ft_get_color_str(t_rgb color);

//save
void		save_scene(t_mrt *mrt);
void		write_to_ppm(t_mrt *mrt);
void		ft_write_planes(t_plane *plane, int count, int fd);
void		ft_write_spheres(t_sphere *sphere, int count, int fd);
void		ft_write_cylinders(t_cylinder *cylinder, int count, int fd);
void		ft_write_triangles(t_triangle *triangle, int count, int fd);
void		ft_write_to_file(char *line, int fd);
char		*ft_write_pos(t_vec pos);
t_vec		ft_unnormalize(t_vec vec);
char		*ft_write_dir(t_vec dir);
char		*ft_write_rgb(t_rgb color);

//bump map
void		set_bump_maps(t_mrt *mrt);
t_vec		bump_nrml_by_coor(t_option *opt, int x, int y, double height);
t_vec		get_bump_nrml(t_vec new_n, t_base tang_base, t_mtrx chg);

#endif