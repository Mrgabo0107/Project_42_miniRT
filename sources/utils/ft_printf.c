/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ionorb <ionorb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:21:07 by ionorb            #+#    #+#             */
/*   Updated: 2023/02/19 14:25:05 by ionorb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int	ft_numlen(long n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa_long(long n)
{
	int		sign;
	int		i;
	char	*result;

	sign = 1;
	i = ft_numlen(n);
	if (n <= 0)
	{
		sign = -1;
		i++;
	}
	result = malloc((i + 1) * sizeof (char));
	if (!result)
		return (NULL);
	result[0] = '-';
	if (n == 0)
		result[0] = '0';
	result[i] = '\0';
	while (--i >= 0 && n != 0)
	{
		result[i] = (n % 10) * sign + 48;
		n /= 10;
	}
	return (result);
}

int	ft_convert(unsigned long dec, int isupper)
{
	char	*base;

	if (isupper)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (dec == 0)
		return (0);
	else
	{
		ft_convert(dec / 16, isupper);
		write(1, &base[dec % 16], 1);
	}
	return (1);
}

int	ft_puthex(unsigned long dec, int isupper)
{
	int	count;

	count = 0;
	if (dec == 0)
	{
		write(1, "0", 1);
		count++;
	}
	ft_convert(dec, isupper);
	while (dec > 0)
	{
		dec /= 16;
		count++;
	}
	return (count);
}

int	ft_putstr(char	*str)
{
	int	i;

	i = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (str[i])
		i++;
	write(1, str, i);
	return (i);
}

int	ft_putnum(int n)
{
	int		count;
	char	*num;

	num = ft_itoa_long(n);
	count = ft_strlen(num);
	write(1, num, count);
	free(num);
	return (count);
}

int	ft_putnum_unsig(unsigned int n)
{
	int		count;
	char	*num;

	num = ft_itoa_long(n);
	count = ft_strlen(num);
	write(1, num, count);
	free(num);
	return (count);
}

// int	ft_strlen(char *str)
// {
// 	int	len;

// 	len = 0;
// 	while (str[len])
// 		len++;
// 	return (len);
// }

int	ft_isint(int c)
{
	if (c == 'c' || c == 'd' || c == 'u' || c == 'p'
		|| c == 'i' || c == 'x' || c == 'X')
		return (1);
	return (0);
}

int	ft_writeint(long long arg, int c)
{
	int	wordcount;

	wordcount = 0;
	if (c == 'c')
		wordcount += write(1, &arg, 1);
	else if (c == 'd' || c == 'i')
		wordcount += ft_putnum((int)arg);
	else if (c == 'u')
		wordcount += ft_putnum_unsig((unsigned int)arg);
	else if (c == 'x')
		wordcount += ft_puthex((unsigned int)arg, 0);
	else if (c == 'X')
		wordcount += ft_puthex((unsigned int)arg, 1);
	else if (c == 'p')
	{
		if (arg == 0)
			return (wordcount += write(1, "(nil)", 5));
		wordcount += write(1, "0x", 2);
		wordcount += ft_puthex(arg, 0);
	}
	return (wordcount);
}

int	ft_printf(const char *input, ...)
{
	int		i;
	int		wordcount;
	va_list	args;

	va_start(args, input);
	wordcount = 0;
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '%')
		{
			i++;
			if (ft_isint(input[i]))
				wordcount += ft_writeint(va_arg(args, long long), input[i]);
			else if (input[i] == 's')
				wordcount += ft_putstr(va_arg(args, char *));
			else if (input[i] == '%')
				wordcount += write(1, "%", 1);
			else
				printf(" ***dat aint right!***");
		}
		else
			wordcount += write(1, &input[i], 1);
		i++;
	}
	va_end(args);
	return (wordcount);
}
