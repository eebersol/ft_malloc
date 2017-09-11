/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 10:20:44 by eebersol          #+#    #+#             */
/*   Updated: 2015/12/01 16:54:49 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;

	if (len == 0)
		return (b);
	str = (unsigned char *)b;
	while (len--)
	{
		*str = (unsigned char)c;
		str++;
	}
	return (b);
}
