/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 01:36:18 by ionorb            #+#    #+#             */
/*   Updated: 2023/02/15 18:02:29 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	ft_print_mem(t_mem *mem)
// {
// 	int	i = 0;

// 	while (mem)
// 	{
// 		i++;
// 		printf("mem: %p\n", mem->ptr);
// 		mem = mem->next;
// 	}
// 	printf("%d\n", i);
// }

void	ft_free(void *ptr)
{
	ft_malloc(ptr, 0);
}

void	ft_quit(int status)
{
	ft_malloc(NULL, status);
}

void	ft_add_to_mem(void *thing)
{
	ft_malloc(thing, ADD_TO_MEM);
}

void	ft_free_one(t_mem *mem, void *thing)
{
	t_mem	*prev;
	t_mem	*after;

	prev = mem;
	if (mem)
		mem = mem->next;
	while (mem && mem->next)
	{
		after = mem->next;
		if (mem->ptr == thing)
		{
			free(mem->ptr);
			free(mem);
			mem = after;
			prev->next = after;
		}
		prev = mem;
		mem = mem->next;
	}
}