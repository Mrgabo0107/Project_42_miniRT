/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ionorb <ionorb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:13:35 by ionorb            #+#    #+#             */
/*   Updated: 2023/02/18 20:05:30 by ionorb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_lst	*ft_lstnew(char *line, t_obj *obj, int type)
{
	t_lst	*new;

	new = (t_lst *)ft_malloc(sizeof(t_lst));
	new->line = line;
	new->obj = obj;
	new->type = type;
	new->next = NULL;
	return (new);
}

t_lst	*ft_lstadd_back(t_lst *lst, t_lst *new)
{
	t_lst	*tmp;

	if (!lst)
		return (new);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (lst);
}

t_table	*ft_tablenew(char **line)
{
	t_table	*new;
	int		i;

	i = 0;
	new = (t_table *)ft_malloc(sizeof(t_table));
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

t_table	*ft_tableadd_new(t_table *table, char **line)
{
	t_table	*new;

	new = ft_tablenew(line);
	table = ft_tableadd_back(table, new);
	return (table);
}
