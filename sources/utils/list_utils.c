/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:13:35 by ionorb            #+#    #+#             */
/*   Updated: 2023/02/19 22:23:08 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_obj	*ft_get_obj(void *obj, int type)
// {
// 	t_obj	*new;

// 	new = (t_obj *)ft_malloc(sizeof(t_obj));
// 	if (type == SPHERE)
// 		new->sphere = (t_sphere)obj;
// 	else if (type == PLANE)
// 		new->plane = (t_plane)obj;
// 	else if (type == CYLINDER)
// 		new->cylinder = (t_cylinder)obj;
// 	else if (type == AMBIENT)
// 		new->amblight = (t_amblight)obj;
// 	else if (type == CAMERA)
// 		new->cam = (t_cam)obj;
// 	else if (type == LIGHT)
// 		new->light = (t_light)obj;
// 	else
// 		new = NULL;
// 	return (new);
// }

// t_lst	*ft_lstnew(void *obj, int type)
// {
// 	t_lst	*new;

// 	new = (t_lst *)ft_malloc(sizeof(t_lst));
// 	new->obj = ft_get_obj(obj, type);
// 	new->type = type;
// 	new->next = NULL;
// 	return (new);
// }

// t_lst	*ft_lstadd_back(t_lst *lst, t_lst *new)
// {
// 	t_lst	*tmp;

// 	if (!lst)
// 		return (new);
// 	tmp = lst;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	tmp->next = new;
// 	return (lst);
// }

// t_lst	*ft_lstadd_new(t_lst *lst, void *obj, int type)
// {
// 	t_lst	*new;

// 	new = ft_lstnew(obj, type);
// 	lst = ft_lstadd_back(lst, new);
// 	return (lst);
// }

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
