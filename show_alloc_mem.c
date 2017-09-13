/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/13 14:47:06 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/malloc.h"

size_t display_block (t_zone *zone)
{
	size_t size_zone;

	size_zone = 0;;
	while (zone->block->next != NULL)
	{
		size_zone += zone->block->size;
		printf("%p - %p : %d octets\n", zone->block->addr, zone->block->addr + 10, zone->block->size);
		zone->block = zone->block->next;
	}
	return (size_zone);
}

void show_alloc_meme (void)
{
	t_zone 		*zone;
	size_t 		size_total;

	zone 		= recover_zone();
	size_total 	= 0;
	while (zone)
	{
		if (zone->type == TINY)
			printf("TINY : %p\n", zone->addr);
		else if (zone->type == SMALL)
			printf("SMALL : %p\n", zone->addr);
		else if (zone->type == LARGE)
			printf("LARGE : %p\n", zone->addr);
		size_total += display_block(zone);
		if (zone->next == NULL)
			break;
		zone = zone->next;
	}
	printf("Total : %lu octets\n", size_total);
}
