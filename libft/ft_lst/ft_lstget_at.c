/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget_at.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 09:57:54 by eebersol          #+#    #+#             */
/*   Updated: 2016/10/14 15:52:43 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstget_at(t_list *lst, int at)
{
	int i;

	i = 0;
	while (lst)
	{
		if (i == at)
			return (lst);
		lst = lst->next;
		i++;
	}
	return (NULL);
}
