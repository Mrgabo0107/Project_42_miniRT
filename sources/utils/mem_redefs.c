/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_redefs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel <yoel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:34:02 by yridgway          #+#    #+#             */
/*   Updated: 2023/04/02 20:27:02 by yoel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*ft_malloc(long long int size)
{
	return (ft_memory(NULL, size));
}

void	ft_free(void *ptr)
{
	printf("freeing %p\n", ptr);
	ft_memory(ptr, FREE_ONE);
}

void	ft_quit(int status)
{
	ft_memory(NULL, status);
}

void	ft_add_to_mem(void *thing)
{
	ft_memory(thing, ADD_TO_MEM);
}

void	ft_get_mem_size(void)
{
	ft_memory(NULL, MEM_SIZE);
}
