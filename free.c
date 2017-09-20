/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/20 09:56:31 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

int 	check_zone(t_zone *zone, void *ptr, int jump)
{
	t_zone *tmpZone;
	void 	*begin;
	int 	i;

	tmpZone = zone;
	begin 	= tmpZone->addr;
	while (tmpZone)
	{
		i = 0;
		begin = tmpZone->addr;
		while (i++ < tmpZone->nbrBlock)
		{
			if (begin + sizeof(int) == ptr)
			{
				tmpZone->nbrBlockUsed--;
				*(int*)(begin - sizeof(int)) = 0;
				return (1);
			}
			begin += jump + sizeof(int);
		}
		if (tmpZone->next == NULL)
			break;
		tmpZone = tmpZone->next;
	}
	return (0);
}

void	free(void *ptr)
{
	t_base 	*base;

	base = recover_base();
	check_zone(base->tiny, ptr, TINY_BLOCK) == 1 ? 0 :
		check_zone(base->small, ptr, SMALL_BLOCK) == 1 ? 0 :
			check_zone(base->large, ptr, 0);
}