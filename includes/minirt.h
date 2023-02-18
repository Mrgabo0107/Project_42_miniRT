/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ionorb <ionorb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:51:33 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/18 21:04:53 by ionorb           ###   ########.fr       */
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

# define WX 4
# define WY 3
# define IX 4
# define IY 3
# define EXIT_ERROR -777
# define ADD_TO_MEM -666
# define EXIT_OK -555
# define FREE_ONE -444
# define SAVE_MLX -333
# define PI 3.1415926536

//error messages
# define TOO_MANY_CAPITALS "Too many capital letters in the scene.\n"
# define MISSING_CAPITALS "Missing capital letters in the scene.\n"

//init
int		init_minirt(t_mrt *mrt);
int		ft_init_mlx(t_mrt *mrt);

//end
int		end_mrt(t_mrt *mrt);

//parsing
int		ft_check_file(char *file);
int		ft_strcmp_1(char *s1, char *s2);

//utils
int		get_next_line(int fd, char **line);

//list
t_lst	*ft_lstnew(char *line, t_obj *obj, int type);
t_lst	*ft_lstadd_back(t_lst *lst, t_lst *new);
t_table	*ft_tablenew(char **line);
t_table	*ft_tableadd_back(t_table *table, t_table *new);
t_table	*ft_tableadd_new(t_table *table, char **line);

//memory
void	*ft_malloc(long long int size);
void	*ft_memory(void *ptr, long long int size);
void	ft_free(void *ptr);
void	ft_free_one(t_mem *mem, void *thing);
void	ft_quit(int status);
void	clean_memory(void);
void	ft_add_to_mem(void *thing);
void	ft_close(int *fd);
void	ft_save_mlx(void *ptr, void **mlx, void **win, void **img);
void	ft_free_mlx(void **mlx, void **win, void **img);

//math
double	int_pow(double basis, int exp);
double	vect_norm(t_vec v);
t_vec	fill_coord(double c1, double c2, double c3);
t_vec	normalize(t_vec v);
t_vec	scalar_by_vector(double scalar, t_vec vector);
t_vec	vector_sum(t_vec v1, t_vec v2);
double	rad_and_deg(double angle, int ctrl);
void	print_vector(t_vec v); //debug

//camera
void	set_all_cam_values(t_cam *cam);

//debug
void	print_pixels_coord(t_cam *cam);

#endif