/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:42:22 by gamoreno          #+#    #+#             */
/*   Updated: 2023/03/27 21:46:42 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static char	*case_cero(char *entera)
{
	char	*temp;

	temp = ft_strjoin("-", entera);
	ft_free(entera);
	return (temp);
}

static double	decimal_move(double d, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		d *= 10;
		i++;
	}
	return (d);
}

static void	free_strings(char *s1, char *s2)
{
	ft_free(s1);
	ft_free(s2);
}

static char	*separator(char *entera)
{
	char	*temp;

	temp = ft_strjoin(entera, ".");
	free (entera);
	return (temp);
}

char	*ft_ftoa(double n)
{
	char	*res;
	char	*entera;
	char	*decimal;
	double	p_entera;
	double	p_decimal;

	p_decimal = modf(n, &p_entera);
	entera = ft_itoa(p_entera);
	if (p_decimal < 0.0 && p_entera == 0.0)
		entera = case_cero(entera);
	if (p_decimal < 0.0)
		p_decimal *= -1;
	p_decimal = decimal_move(p_decimal, 5);
	decimal = ft_itoa((int)(p_decimal));
	entera = separator(entera);
	res = ft_strjoin(entera, decimal);
	free_strings(entera, decimal);
	return (res);
}
