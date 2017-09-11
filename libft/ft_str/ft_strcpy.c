/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 14:50:59 by eebersol          #+#    #+#             */
/*   Updated: 2016/01/30 14:41:16 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
** NAME : strcpy
** DESCRIPTION : La fonction strcpy() copie la chaîne pointée par src (y
** compris l'octet nul « \0 » final) dans la chaîne pointée par dest. Les deux
** chaînes ne doivent pas se chevaucher. La chaîne dest doit être assez grande
** pour accueillir la copie.
** PARAM : dst -> la chaine de caractere de destination
** PARAM : src -> la chaine de caractere de source
** RETURN : renvoient un pointeur sur la chaîne destination dest.
*/

char	*ft_strcpy(char *dst, const char *src)
{
	char *ret;

	ret = dst;
	while (*src)
	{
		*dst = *src;
		src++;
		dst++;
	}
	*dst = '\0';
	return (ret);
}
