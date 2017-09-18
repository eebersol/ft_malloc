/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/15 14:57:59 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/malloc.h"

size_t display_block (t_zone *zone)
{
	size_t size_zone;
	void 	*ptr;
	int i;

	i = 0;
	size_zone = 0;
	ptr = zone->addr;
	while (i < zone->nbrBlock)
	{
		// size_zone += *(int*)ptr;
		printf("[%d] %p - %p : %d octets\n", i, ptr, (ptr + TINY_BLOCK + (sizeof(int))), *(int*)ptr);
		i++;
	}
	return (0);
}

void show_alloc_meme ()
{
	t_global_ref *ref;
	t_base 		*base;
	t_zone 		*zone;
	size_t 		size_total;

	printf("AQUI\n");
	zone 		= NULL;
	ref = recover_global_ref();
	base = recover_base();
	size_total 	= 0;
	printf("AQUI\n");
	if (base)
	{
		if (base->tiny)
		{
			printf("TINY : %p\n", zone->addr);
			size_total += display_block(base->tiny);
		}
		else if (base->small)
		{
			printf("SMALL : %p\n", zone->addr);
			size_total += display_block(base->small);
		}
		else if (base->large)
		{
			printf("LARGE : %p\n", zone->addr);
			size_total += display_block(base->large);
		}
	}
	printf("Total : %lu octets\n", size_total);
}
