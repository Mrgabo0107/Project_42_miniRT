/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel <yoel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:51:33 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/13 23:41:25 by yoel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "libft.h"
# include "structs.h"
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

// # define WX 10
// # define WY 5
// # define IX 10
// # define IY 5
# define WX 801
# define WY 401
# define IX 801
# define IY 401
// # define WX 2000
// # define WY 1000
// # define IX 2000
// # define IY 1000
# define EXIT_ERROR -777
# define ADD_TO_MEM -666
# define EXIT_OK -555
# define FREE_ONE -444
# define SAVE_MLX -333
# define SAVE_FD -222
# define PI 3.1415926536
# define BUFFER_SIZE 10000

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define Q 113
# define E 101
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define PLUS 65451
# define MINUS 65453
# define SPACE 32
# define SHIFT 65505
# define CTRL 65507
# define R 114
# define T 116
# define ENTER 65293
// # define COMMENT 123

//error messages
# define TOO_MANY_CAPITALS "Too many capital letters in the scene"
# define MISSING_CAPITALS "Missing capital letters in the scene"
# define TOO_MANY_AMBIENTS "Too many ambient lights in the scene"
# define TOO_MANY_CAMERAS "Too many cameras in the scene"
# define MISSING_AMBIENT "Missing ambient light in the scene"
# define MISSING_CAMERA "Missing camera in the scene"
# define MISSING_LIGHT "Missing light in the scene"
# define CAPITAL_INSTRUCTIONS "\
\nAdd one (C)amera, one (A)mbient and at least one (L)ight in the scene"
# define CYLINDER_INSTRUCTIONS "\
\n(cy)linder: [name: 'cy', pos: (x,y,z), dir: (a,b,c), diameter, height, \
color: (r,g,b)] \
\ne.g. cy 0,0,0 0,1,0 3 8 255,0,0"
# define SPHERE_INSTRUCTIONS "\
\n(sp)here: [name: 'sp', pos: (x,y,z), diameter [-1000,1000], color: (r,g,b)] \
\ne.g. sp 0,0,0 3 255,0,0"
# define PLANE_INSTRUCTIONS "\
\n(pl)ane: [name: 'pl', pos: (x,y,z), dir: (a,b,c), color: (r,g,b)] \
\ne.g. pl 0,0,0 0,1,0 255,0,0"
# define LIGHT_INSTRUCTIONS "\
\n(L)ight: [name: 'L', pos: (x,y,z), brightness: [0.0,1.0], color: (r,g,b)] \
\ne.g. l 0,0,0 0.5 255,0,0"
# define CAMERA_INSTRUCTIONS "\
\n(C)amera: [name: 'C', pos: (x,y,z), dir: (a,b,c), fov: [0-180]] \
\ne.g. c 0,0,0 0,1,0 90"
# define AMBIENT_INSTRUCTIONS "\
\n(A)mbient: [name: 'A' brightness: [0.0,1.0], color: (r,g,b)] \
\ne.g. a 0.5 255,0,0"
# define RGB_INSTRUCTIONS "\
\nRGB must be three integers between 0 and 255 and \
separated by commas: (r,g,b)\ne.g. 255,0,0"
# define RATIO_INSTRUCTIONS "\
\nRatio must be a floating point integer between 0 and 1 \
\ne.g. 0.5"
# define FOV_INSTRUCTIONS "\
\nFOV must be an integer between 0 and 180 \
\ne.g. 90"
# define POS_INSTRUCTIONS "\
\nPosition must be three floating point integers between -1000 and 1000 \
seperated by commas \
\ne.g. -24.5,15.433,20"
# define SIZE_INSTRUCTIONS "\
\nSize must be a floating point integer between 0 and 1000 \
\ne.g. 3.5"
# define NORMAL_INSTRUCTIONS "\
\nNormal must be three floating point integers between -1 and 1 seperated by \
commas, at least one value should be non-zero \
\ne.g. 0,1,-0.5"
# define OBJECT_INSTRUCTIONS "\
\nValid objects include: \
\n(C)amera, (L)ight, (A)mbient light, (sp)here, (pl)ane and (cy)linder"
# define INVALID_FILE "Invalid file"
# define FILE_INSTRUCTIONS "\
\nPlease provide an existing file path, with the correct \
permissions and ending in '.rt'"
# define INVALID_OBJECT "Invalid object in the scene"
# define FILE_ERROR "Failed to open file"
# define CLEAN_EXIT "Program Exited Correctly :)"
# define INT_RANGE "All values must be between INT_MAX (-2147483648) and \
INT_MIN (2147483647)"
# define DOUBLE_RANGE "Double must have a precision of less than 15 digits"
# define NORMAL_RANGE "Normal must be between -1 and 1"
# define RGB_RANGE "RGB must be between 0 and 255"
# define FOV_RANGE "FOV must be between 0 and 180"
# define RATIO_RANGE "Ratio must be between 0 and 1"
# define POS_RANGE "Position must be between -1000 and 1000"
# define SIZE_RANGE "Size must be between 0 and 1000"

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
t_base		get_cyl_base(t_vec	dir);
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

//plane
t_vec		get_normal_plane(t_mrt *mrt, t_inter inter);
void		check_planes(t_mrt *mrt, t_inter *ctrl, t_vec point, t_vec dir);

//sphere
t_vec		get_normal_sphere(t_mrt *mrt, t_inter inter);
void		check_spheres(t_mrt *mrt, t_inter *ctrl, t_vec point, t_vec dir);
t_discr		get_sph_dscr(t_vec ncam, t_vec dir, double square_rad);

//cylinder
t_vec		get_normal_cylinder(t_mrt *mrt, t_inter inter);
void		check_cylinders(t_mrt *mrt, t_inter *ctrl, t_vec point, t_vec dir);

//camera
t_inter		check_intersections(t_mrt *mrt, t_vec point, t_vec dir);
void		set_all_cam_values(t_cam *cam);
t_vec		screen_pxl_by_indx(t_cam *cam, int i, int j);
void		my_mlx_pixel_put(t_mrt *mrt, int x, int y, int color);
void		pixel_calcul(t_mrt *mrt);
int			get_pixel_color(t_mrt *mrt, int x, int y);
double		distance_to_cap(t_vec start_pos, t_cylinder cylinder, t_vec ray);
t_inter		fill_ctrl(t_mrt *mrt, int type, int index, double dist);

//color
t_rgb		get_color(t_mrt *mrt, t_inter *ctr, t_vec dir);
t_rgb		ft_make_rgb(int r, int g, int b);
t_rgb		ft_make_rgb_ratio(t_rgb color);
t_rgb		normalize_color(t_rgb color);
t_rgb		show_light_sources(t_mrt *mrt, t_rgb color, t_vec dir);
double		get_angle_between(t_vec v1, t_vec v2);

int			key_press(int key, t_mrt *mrt);

#endif