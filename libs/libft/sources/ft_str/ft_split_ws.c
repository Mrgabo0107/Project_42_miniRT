/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ws.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel <yoel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:29:33 by ionorb            #+#    #+#             */
/*   Updated: 2023/04/03 22:09:43 by yoel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isws(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	ft_len(char const *s)
{
	int	k;
	int	len;

	k = 0;
	len = 0;
	while (s[k] && !ft_isws(s[k]))
	{
		len++;
		k++;
	}
	return (len);
}

char	**ft_makearr(char const *s)
{
	char	**arr;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && ft_isws(s[i]))
			i++;
		if (s[i])
			count++;
		while (s[i] && !ft_isws(s[i]))
			i++;
	}
	arr = ft_malloc((count + 1) * sizeof (char *));
	if (!arr)
		return (NULL);
	return (arr);
}

char	*ft_putword(char const *s)
{
	char	*word;
	int		k;

	k = 0;
	word = ft_malloc((ft_len(s) + 1) * sizeof (char));
	if (!word)
		return (NULL);
	while (s[k] && !ft_isws(s[k]))
	{
		word[k] = s[k];
		k++;
	}
	word[k] = '\0';
	return (word);
}

char	**ft_split_ws(char const *s)
{
	int		i;
	int		k;
	char	**arr;

	arr = ft_makearr(s);
	if (!arr)
		return (NULL);
	i = 0;
	k = 0;
	while (s[k])
	{
		while (s[k] && ft_isws(s[k]))
			k++;
		if (s[k])
		{
			arr[i] = ft_putword((s + k));
			i++;
		}
		while (s[k] && !ft_isws(s[k]))
			k++;
	}
	arr[i] = 0;
	return (arr);
}
