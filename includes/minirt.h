/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:51:33 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/26 18:13:17 by ana              ###   ########.fr       */
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

// # define WX 10
// # define WY 5
// # define IX 10
// # define IY 5
# define WX 2000
# define WY 1000
# define IX 2000
# define IY 1000
# define EXIT_ERROR -777
# define ADD_TO_MEM -666
# define EXIT_OK -555
# define FREE_ONE -444
# define SAVE_MLX -333
# define PI 3.1415926536

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

//error messages
# define TOO_MANY_CAPITALS "Too many capital letters in the scene"
# define MISSING_CAPITALS "Missing capital letters in the scene"
# define INVALID_OBJECT "Invalid object in the scene"
# define FILE_ERROR "Failed to open file"
# define CLEAN_EXIT "Program Exited Correctly :)"

//init
int			init_minirt(t_mrt *mrt);
int			ft_init_mlx(t_mrt *mrt);

//end
int			end_mrt(t_mrt *mrt);

//parsing
int			ft_parse(t_mrt *mrt, char *file);
int			ft_strcmp_1(char *s1, char *s2);
int			eval_obj(char *line);
t_table		*ft_fill_table(char *file);
int			ft_arg_count(char **line);
void		ft_error(char *msg, char *extra);

//cell filling
int			ft_check_chars(char **line, char *chars);
double		ft_fill_ratio(char *cell);
uint		ft_fill_rgb(char *cell);
t_vec		ft_fill_pos(char *cell, int dir);
double		ft_fill_size(char *cell, int fov);
// double		ft_fill_fov(char *cell);

//fill objects
// t_amblight	ft_fill_ambient(char *line[7]);
t_cam		ft_fill_cam(char *line[7]);
t_light		ft_fill_light(char *line[7], int amb);
t_sphere	ft_fill_sphere(char *line[7]);
t_plane		ft_fill_plane(char *line[7]);
t_cylinder	ft_fill_cylinder(char *line[7]);

//utils
int			get_next_line(int fd, char **line);

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
void		ft_close(int *fd);
void		ft_save_mlx(void *ptr, void **mlx, void **win, void **img);
void		ft_free_mlx(void **mlx, void **win, void **img);

//free
void		ft_free_array(char **array);

//math
double		int_pow(double basis, int exp);
double		vect_norm(t_vec v);
t_vec		fill_coord(double c1, double c2, double c3);
t_vec		normalize(t_vec v);
t_vec		scal_vec(double scalar, t_vec vector);
t_vec		vec_sum(t_vec v1, t_vec v2);
t_vec		vec_sub(t_vec v1, t_vec v2);
double		rad_and_deg(double angle, int ctrl);
void		print_vector(t_vec v); //debug
double		min_v(double d1, double d2);
double		max_v(double d1, double d2);
double		v_abs(double x);
double		dot_prod(t_vec v1, t_vec v2);
t_vec		cross_prod(t_vec v1, t_vec v2);
double		vec_len(t_vec v);
t_vec		vec_rest(t_vec v1, t_vec v2);
double		norm_raised_2(t_vec v);
t_base		get_cyl_base(t_vec	dir);
t_vec		mtrx_by_vec(t_mtrx m, t_vec v);
double		mtrx_det(t_mtrx m);
t_mtrx		mtrx_trsp(t_mtrx m);

//plane
// double		distance_to_plane(t_vec point, t_vec pos, t_vec dir, t_vec ray);
double		perp_to_plane(t_vec point, t_vec plane_pos, t_vec plane_norm);

//camera
void		set_all_cam_values(t_cam *cam);
t_vec		screen_pxl_by_indx(t_cam *cam, int i, int j);
void		my_mlx_pixel_put(t_mrt *mrt, int x, int y, int color);
void		pixel_calcul(t_mrt *mrt);
uint		get_pixel_color(t_mrt *mrt, int x, int y);
void		check_spheres(t_mrt *mrt, t_inter *ctrl, t_vec dir);
void		check_cylinders(t_mrt *mrt, t_inter *ctrl, t_vec dir);
void		check_planes(t_mrt *mrt, t_inter *ctrl, t_vec dir);


//debug
void		print_pixels_coord(t_cam *cam);

int			ft_printf(const char *input, ...);
void		ft_printf_objects(t_mrt *mrt);

#endif