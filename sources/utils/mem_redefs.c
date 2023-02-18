/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_redefs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ionorb <ionorb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:34:02 by yridgway          #+#    #+#             */
/*   Updated: 2023/02/18 18:18:25 by ionorb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*ft_malloc(long long int size)
{
	return (ft_memory(NULL, size));
}

void	ft_free(void *ptr)
{
	ft_memory(ptr, 0);
}

void	ft_quit(int status)
{
	ft_memory(NULL, status);
}

void	ft_add_to_mem(void *thing)
{
	ft_memory(thing, ADD_TO_MEM);
}
