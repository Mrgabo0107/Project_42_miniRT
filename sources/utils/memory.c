/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:34:04 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/15 18:03:26 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*ft_liberate(t_mem *mem, int type)
{
	t_mem	*prev;

	/*free linked lists here*/
	while (mem)
	{
		if (mem->ptr)
			free(mem->ptr);
		prev = mem;
		mem = mem->next;
		free(prev);
	}
	if (type == EXIT_ERROR)
		exit(1);
	else if (type == EXIT_SUCCESS)
		exit(0);
	return (NULL);
}

t_mem	*mem_addback(t_mem **mem, t_mem *new)
{
	t_mem	*tmp;

	tmp = *mem;
	if (!new)
		return (ft_liberate(*mem, EXIT_ERROR), NULL);
	if (!tmp)
		return (mem = &new, *mem);
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (*mem);
}

t_mem	*mem_new(size_t size, void *thing)
{
	t_mem	*new;
	char	*err;

	err = "Error: malloc failed\n";
	new = malloc(sizeof(t_mem));
	if (!new)
		return (ft_putstr_fd(err, 2), NULL);
	if (thing)
		new->ptr = thing;
	else
		new->ptr = malloc(size);
	if (!new->ptr)
	{
		ft_putstr_fd(err, 2);
		free(new);
		new = NULL;
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

void	*ft_malloc(void *ptr, long long int size)
{
	static t_mem	*mem = NULL;
	t_mem			*new;

	if (ptr && size == ADD_TO_MEM)
		return (mem = mem_addback(&mem, mem_new(0, ptr)));
	if (ptr && size == FREE_ONE)
		return (ft_free_one(mem, ptr), NULL);
	if (size == EXIT_ERROR || size == EXIT_SUCCESS)
		return (mem = ft_liberate(mem, size), NULL);
	new = mem_new(size, NULL);
	mem = mem_addback(&mem, new);
	return (new->ptr);
}