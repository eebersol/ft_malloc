/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/21 15:55:44 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void 	*smap(size_t len)
{
	size_t  	multiple;

	multiple 	= (len / PAGE_SIZE) + 1;
	len 		= multiple * PAGE_SIZE;
	return (mmap(NULL, len, PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0));
}

void 	save_zone(t_base *base, t_zone *zoneList)
{
	if (base->type == TINY)
		base->tiny = zoneList;
	else if (base->type == SMALL)
		base->small = zoneList;
	else if (base->type == LARGE)
		base->large = zoneList;
}

t_zone 	*create_zone(size_t size)
{
	t_zone 				*zone;
	t_base 				*base;
	size_t 				sizeTotal;
	void 				*begin;
	int 				i;

	i 					= 0;
	sizeTotal 			= get_nbr_block(size);
	base 				= recover_base();	
	zone 	 			= base->type == TINY ?  (t_zone *)smap((sizeof(t_zone)) + ((sizeof(int) + TINY_BLOCK) * sizeTotal)) :
							base->type == SMALL ? (t_zone *)smap((sizeof(t_zone)) + ((sizeof(int) + SMALL_BLOCK) * sizeTotal)) :
								(t_zone *)smap((sizeof(t_zone)) + ((sizeof(int) + size)));
	zone->nbr_block_used 	= 0;
	zone->addr 			= &zone[0] + sizeof(t_zone);
	zone->nbr_block 		= base->type == LARGE ? 1 : sizeTotal;
	zone->next 			= NULL;
	zone->type 			= get_type(size);
	begin 				= zone->addr;

	while (i++ < zone->nbr_block)
	{
		*(int*)begin = 0;
		begin 			+= (base->type == TINY ? TINY_BLOCK : base->type == SMALL ? SMALL_BLOCK : size) + sizeof(int);
	}
	return (zone);
}


int		count_len_zone(t_zone *lst)
{
	int			i;
	t_zone		*elem;

	i 			= 0;
	elem 		= lst;
	if (elem)
	{
		while (elem)
		{
			i++;
			elem = elem->next;
		}
	}
	return (i);
}
