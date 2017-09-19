/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/19 16:26:31 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/malloc.h"

size_t display_block (t_zone *zone, t_zone_type type)
{
	size_t 				size_zone;
	void 				*ptr;
	int 				i;
	int 				size;
	int 				size_total;

	i 					= 0;
	size 				= 0;
	size_zone 			= 0;
	size_total 			= 0;
	ptr 				= zone->addr;
	while (i < zone->nbrBlock)
	{
		if (*(int*)ptr != 0)
		{
			size 		= *(int*)ptr;
			size_total += size;
			printf("[%d] %p - %p : %d octets\n",i,  ptr, ptr  + sizeof(int) + *(int*)ptr, size);
			ptr 		+= sizeof(int);
			ptr 		+= type == TINY ? TINY_BLOCK : type == SMALL ?  SMALL_BLOCK : LARGE_ZONE;
		}
		else
			ptr 		+= (sizeof(int)) + type == TINY ? TINY_BLOCK : type == SMALL ? SMALL_BLOCK : LARGE;
		// else if (type == TINY)
		// 	ptr += (sizeof(int)) + TINY_BLOCK;
		// else if (type == SMALL)
		// {
		// 	ptr += (sizeof(int)) + SMALL_BLOCK;
		// }
		// else if (type == LARGE)
		// 	ptr += (sizeof(int)) + sizeof(LARGE);
		i++;
	}
	return (size_total);
}

void show_alloc_meme ()
{
	t_global_ref *ref;
	t_base 		*base;
	t_zone 		*zone;
	size_t 		size_total;
	int 		i;

	zone 		= NULL;
	ref = recover_global_ref();
	base = recover_base();
	size_total 	= 0;
	i = 0;
	printf("Show_alloc_meme : \n");
	printf("Len tiny  : [%d] \n", ft_lstcount(base->tiny));
	printf("Len small : [%d] \n", ft_lstcount(base->small));
	printf("Len large : [%d] \n", ft_lstcount(base->large));
	if (base)
	{
		while (base->tiny)
		{
			printf(" [%d] TINY : %p\n", i, base->tiny->addr);
			size_total += display_block(base->tiny, ref->type);
			if (base->tiny->next == NULL)
				break ;
			base->tiny = base->tiny->next;
			i++;
		}
		while (base->small)
		{
			printf("SMALL : %p\n", base->small->addr);
			size_total += display_block(base->small, ref->type);
			if (base->small->next == NULL)
				break ;
			base->small = base->small->next;
		}
		while (base->large)
		{
			printf("LARGE : %p\n", base->large->addr);
			size_total += display_block(base->large, ref->type);
			if (base->large->next == NULL)
				break ;
			base->large = base->large->next;
		}
	}
	printf("Total : %lu octets\n", size_total);
}
