/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:13:35 by ionorb            #+#    #+#             */
/*   Updated: 2023/03/24 21:39:17 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_table	*ft_tablenew(char **line, int num_objs)
{
	t_table	*new;
	int		i;

	i = 0;
	new = (t_table *)ft_malloc(sizeof(t_table));
	new->line = (char **)ft_malloc(sizeof(char *) * num_objs);
	while (line && line[i] && i < 7)
	{
		new->line[i] = line[i];
		i++;
	}
	while (i < 7)
		new->line[i++] = NULL;
	new->next = NULL;
	return (new);
}

t_table	*ft_tableadd_back(t_table *table, t_table *new)
{
	t_table	*tmp;

	if (!table)
		return (new);
	tmp = table;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (table);
}

t_table	*ft_tableadd_new(t_table *table, char **line, int num_objs)
{
	t_table	*new;

	new = ft_tablenew(line, num_objs);
	table = ft_tableadd_back(table, new);
	return (table);
}
