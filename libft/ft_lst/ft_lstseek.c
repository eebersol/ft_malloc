/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstseek.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:17 by eebersol          #+#    #+#             */
/*   Updated: 2016/10/12 16:15:54 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list		*ft_lst_seek(t_list *list, char *str)
{
	while (list)
	{
		if (ft_strcmp((char*)list->content, str) == 0)
			return (list);
		else
			list = list->next;
	}
	return (NULL);
}
