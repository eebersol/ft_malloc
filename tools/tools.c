/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/13 15:25:29 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void 	*smap(size_t len)
{
	return (mmap(NULL, len, PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0));
}

t_block *create_block(size_t len)
{
	t_block *block;

	block 		= smap(len);
	block->size = len;
	block->next = NULL;
	block->free = 0;
	block->addr = (void*)&block[0];
	return (block);
}

t_zone *create_zone()
{
	t_zone *zone;

	zone 		= smap(sizeof(zone));
	zone->addr 	= NULL;
	zone->block = NULL;
	zone->next 	= NULL;
	return (zone);
}
