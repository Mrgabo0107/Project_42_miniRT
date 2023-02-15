/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:51:33 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/15 18:00:26 by yridgway         ###   ########.fr       */
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

# define WX 500
# define WY 500
# define IX 500
# define IY 500
# define EXIT_ERROR -777
# define ADD_TO_MEM -666
# define EXIT_OK -555
# define FREE_ONE -444

//init
int		init_minirt(t_mrt *mrt);

//end
int		end_mrt(t_mrt *mrt);

//parsing
int		ft_check_file(char *file);

//utils
int		get_next_line(int fd, char **line);

//memory
void	*ft_malloc(void *ptr, long long int size);
void	ft_free(void *ptr);
void	ft_free_one(t_mem *mem, void *thing);
void	ft_quit(int status);
void	clean_memory(void);
void	ft_add_to_mem(void *thing);
void	ft_close(int *fd);

#endif