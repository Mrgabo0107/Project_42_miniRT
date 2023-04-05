/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:34:02 by yridgway          #+#    #+#             */
/*   Updated: 2023/04/05 03:09:57 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_free(array[i]);
		i++;
	}
	ft_free(array);
}

void	ft_free_table(t_table *table)
{
	t_table	*tmp;

	while (table)
	{
		tmp = table;
		table = table->next;
		ft_free_array(tmp->line);
		ft_free(tmp);
	}
}
