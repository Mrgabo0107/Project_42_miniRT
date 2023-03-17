/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel <yoel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 22:12:17 by yoel              #+#    #+#             */
/*   Updated: 2023/03/17 22:35:02 by yoel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	ft_fill_check(char **line)
{
	t_rgb	color;

	if (ft_arg_count(line) != 2)
		ft_error("Wrong number of arguments for check", \
		CHECK_INSTRUCTIONS, NULL);
	color = ft_fill_rgb(line[1]);
	return (color);
}

double	ft_fill_specular(char **line)
{
	double	specular;

	if (ft_arg_count(line) != 2)
		ft_error("Wrong number of arguments for specular", \
		SPECULAR_INSTRUCTIONS, NULL);
	specular = ft_fill_size(line[1], 0);
	return (specular);
}

double	ft_fill_mirror(char **line)
{
	double	mirror;

	if (ft_arg_count(line) != 2)
		ft_error("Wrong number of arguments for mirror", \
		MIRROR_INSTRUCTIONS, NULL);
	mirror = ft_fill_size(line[1], 0);
	return (mirror);
}

void	ft_fill_options(t_table *table, t_rgb *color, double *specular, \
double *mirror)
{
	while (table && table->next && eval_obj(table->next->line[0]) == OPTION)
	{
		if (eval_option(table->next->line[0]) == CHECKERBOARD)
			*color = ft_fill_check(table->next->line);
		if (eval_option(table->next->line[0]) == SPECULAR)
			*specular = ft_fill_specular(table->next->line);
		if (eval_option(table->next->line[0]) == MIRROR)
			*mirror = ft_fill_mirror(table->next->line);
		table = table->next;
	}
}
