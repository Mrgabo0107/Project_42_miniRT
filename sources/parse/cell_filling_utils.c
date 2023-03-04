/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cell_filling_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 01:10:31 by ana               #+#    #+#             */
/*   Updated: 2023/03/04 01:11:11 by ana              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_check_dots_and_minus(char *str)
{
	int	dot;
	int	minus;
	int	i;

	i = 0;
	dot = 0;
	minus = 0;
	while (str[i])
	{
		if (str[i] == '.')
			dot++;
		if (str[i] == '-')
			minus++;
		if (dot > 1)
			ft_error("Multiple dots(.) in value", str, NULL);
		if (minus > 1)
			ft_error("Multiple minuses(-) in value", str, NULL);
		if (i > 0 && str[i] == '-' && str[i - 1] != ' ')
			ft_error("Minus(-) in value", str, NULL);
		if (str[i] == '.' && !str[i + 1])
			ft_error("Dot(.) in value", str, NULL);
		i++;
	}
}

int	check_valid_number(char *str)
{
	int	i;
	int	count;
	int	minus;

	count = 0;
	i = 0;
	ft_check_dots_and_minus(str);
	while (str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		count++;
		i++;
		if (count > 10)
			return (ft_error(INT_RANGE, str, NULL), 0);
	}
	if (str[i++] == '.')
	{
		count = 0;
		while (str[i + count] >= '0' && str[i + count] <= '9' && count < 15)
			count++;
	}
	if (count >= 15)
		return (ft_error(DOUBLE_RANGE, str, NULL), 0);
	return (1);
}

void	valid_nums(char **line)
{
	while (line && *line)
		check_valid_number(*line++);
}

int	check_for_chars(char *str, char *cell)
{
	int	i;

	i = 0;
	while (cell && cell[i])
	{
		if ((cell[i] == '.' && cell[i + 1] == '-') || \
		(cell[i] == '-' && cell[i + 1] == ',') || \
		(cell[i] == '-' && cell[i + 1] == '.') || \
		(cell[i] == ',' && cell[i + 1] == '.') || \
		(cell[i] == '.' && cell[i + 1] == ','))
			return (1);
		if (!ft_strchr(str, cell[i]))
			return (1);
		i++;
	}
	if (!cell || !cell[0] || cell[0] == ',' || cell[i - 1] == ',' \
	|| cell[0] == '.' || cell[i - 1] == '.')
		return (1);
	return (0);
}

int	out_of_range(double num, double min, double max)
{
	if (num < min || num > max)
		return (1);
	return (0);
}
