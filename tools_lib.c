/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/25 14:51:32 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

void	ft_putnbr(int n)
{
	char c;

	if (n == -2147483648)
		ft_putstr("-2147483648");
	else
	{
		if (n < 0)
		{
			n = -n;
			c = '-';
			write(1, &c, 1);
		}
		if (n >= 10)
		{
			ft_putnbr(n / 10);
			ft_putnbr(n % 10);
		}
		else
		{
			c = '0' + n;
			write(1, &c, 1);
		}
	}
}

void 	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}


char	*ft_itohex(void *ptr)
{
	unsigned long long	address;
	char				*base;
	char				hex[50];
	char 				*str;
	int					i;

	base = "0123456789abcdef";
	address = (unsigned long long)ptr;
	i = 500;
	while (address)
	{
		hex[i] = base[address % 16];
		address = address / 16;
		i--;
	}
	str = &hex[i+1];
	return(str);
}