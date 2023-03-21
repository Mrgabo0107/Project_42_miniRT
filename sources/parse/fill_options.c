/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel <yoel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 22:12:17 by yoel              #+#    #+#             */
/*   Updated: 2023/03/19 23:43:17 by yoel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_fill_check(char **line, t_option *option)
{
	if (ft_arg_count(line) != 2)
		ft_error("Wrong number of arguments for check", \
		CHECK_INSTRUCTIONS, NULL);
	option->check_color = ft_fill_rgb(line[1]);
}

void	ft_fill_specular(char **line, t_option *option)
{
	if (ft_arg_count(line) != 3)
		ft_error("Wrong number of arguments for specular", \
		SPECULAR_INSTRUCTIONS, NULL);
	option->specular[0] = ft_fill_size(line[1], 0);
	option->specular[1] = ft_fill_size(line[2], 0);
}

void	ft_fill_mirror(char **line, t_option *option)
{
	if (ft_arg_count(line) != 2)
		ft_error("Wrong number of arguments for mirror", \
		MIRROR_INSTRUCTIONS, NULL);
	option->mirror = ft_fill_size(line[1], 0);
}

t_option	ft_fill_options(t_table *table)
{
	t_option	option;

	option = (t_option){0, ft_make_rgb(0, 0, 0), 0};
	while (table && table->next && eval_obj(table->next->line[0]) == OPTION)
	{
		if (eval_option(table->next->line[0]) == CHECKERBOARD)
			ft_fill_check(table->next->line, &option);
		if (eval_option(table->next->line[0]) == SPECULAR)
			ft_fill_specular(table->next->line, &option);
		if (eval_option(table->next->line[0]) == MIRROR)
			ft_fill_mirror(table->next->line, &option);
		table = table->next;
	}
	return (option);
}