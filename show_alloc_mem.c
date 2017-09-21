/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/21 14:03:53 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/malloc.h"

size_t display_block (t_zone *zone, int jump)
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
	while (i++ < zone->nbrBlock)
	{
		if (*(int*)ptr != 0)
		{
			size 		= *(int*)ptr;
			printf("   [%d] %p - %p : %d octets\n",i, ptr  + sizeof(int), ptr + jump + sizeof(int), *(int*)ptr);
			ptr 		+= sizeof(int);
			jump 		= jump == 0 ? size : jump;
			ptr 		+= jump;
			size_total += size;
		}
		else
			ptr 		+= (sizeof(int)) + jump;
	}
	return (size_total);
}

void show_alloc_meme ()
{
	t_base 		*base;
	t_zone 		*zone;
	size_t 		size_total;
	int 		jump;
	int 		i;

	zone 		= NULL;
	base 		= recover_base();
	size_total 	= 0;
	i 			= 0;
	jump 		= 0;
	printf("\n-----------------------------------------------------\n\n");
	printf("Show_alloc_meme : \n\n");
	printf("Len tiny  : [%d] \n", ft_lstcount(base->tiny));
	printf("Len small : [%d] \n", ft_lstcount(base->small));
	printf("Len large : [%d] \n", ft_lstcount(base->large));

	if (base)
	{
		zone = base->tiny;
		jump = TINY_BLOCK;
		while (zone)
		{
			printf("\n- n°%d TINY : %p -\n\n", i, zone->addr);
			size_total += display_block(zone, jump);
			if (zone->next == NULL)
				break ;
			zone = zone->next;
			i++;
		}
		zone = base->small;
		jump = SMALL_BLOCK;
		i = 0;
		while (zone)
		{
			printf("\n- n°%d SMALL : %p -\n\n", i, zone->addr);
			size_total += display_block(zone, jump);
			if (zone->next == NULL)
				break ;
			zone = zone->next;
			i++;
		}
		zone = base->large;
		i= 0;
		while (zone)
		{
			printf("\n- n°%d LARGE : %p -\n\n", i, zone->addr);
			size_total += display_block(zone, jump);
			if (zone->next == NULL)
				break ;
			zone = zone->next;
			i++;
		}
	}
	printf("\nTotal : %lu octets\n", size_total);
	printf("\n-----------------------------------------------------\n");
}
