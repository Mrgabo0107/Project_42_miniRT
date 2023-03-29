/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 22:59:39 by yridgway          #+#    #+#             */
/*   Updated: 2023/03/29 22:59:46 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_strcmp_1(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

int	eval_option(char *line)
{
	if (ft_strcmp_1(line, "mir") == 0)
		return (MIRROR);
	if (ft_strcmp_1(line, "check") == 0)
		return (CHECK);
	if (ft_strcmp_1(line, "trans") == 0)
		return (TRANSPARENT);
	if (ft_strcmp_1(line, "spec") == 0)
		return (SPECULAR);
	if (ft_strcmp_1(line, "bump") == 0)
		return (BUMPMAP);
	return (-1);
}

int	eval_obj(char *line)
{
	if (ft_strcmp_1(line, "sp") == 0)
		return (SPHERE);
	if (ft_strcmp_1(line, "pl") == 0)
		return (PLANE);
	if (ft_strcmp_1(line, "cy") == 0)
		return (CYLINDER);
	if (ft_strcmp_1(line, "co") == 0)
		return (CONE);
	if (ft_strcmp_1(line, "L") == 0)
		return (LIGHT);
	if (ft_strcmp_1(line, "A") == 0)
		return (AMBIENT);
	if (ft_strcmp_1(line, "C") == 0)
		return (CAMERA);
	if (eval_option(line) != -1)
		return (OPTION);
	return (-1);
}
