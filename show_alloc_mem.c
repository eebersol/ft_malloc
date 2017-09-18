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

// size_t display_block (t_zone *zone)
// {
// 	size_t size_zone;
// 	int i;

// 	i = 0;
// 	size_zone = 0;;
// 	while (zone->block)
// 	{
// 		size_zone += zone->block->size;
// 		printf("[%d] %p - %p : %d octets\n", i, zone->block->addr, zone->block->addr + 10, zone->block->size);
// 		if (zone->block->next == NULL)
// 			break;
// 		zone->block = zone->block->next;
// 		i++;
// 	}
// 	return (size_zone);
// }

// void show_alloc_meme ()
// {
// 	t_zone 		*zone;
// 	size_t 		size_total;

// 	zone 		= NULL;
// 	size_total 	= 0;
// 	if (zone)
// 	{
// 		while (zone)
// 		{
// 			if (zone->type == TINY)
// 				printf("TINY : %p\n", zone->addr);
// 			else if (zone->type == SMALL)
// 				printf("SMALL : %p\n", zone->addr);
// 			else if (zone->type == LARGE)
// 				printf("LARGE : %p\n", zone->addr);
// 			size_total += display_block(zone);
// 			if (zone->next == NULL)
// 				break;
// 			zone = zone->next;
// 		}
// 	}
// 	printf("Total : %lu octets\n", size_total);
// }
