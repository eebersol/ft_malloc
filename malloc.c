/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/21 14:27:17 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

void 	save_zone(t_base *base, t_zone *zoneList)
{
	if (base->type == TINY)
		base->tiny = zoneList;
	else if (base->type == SMALL)
		base->small = zoneList;
	else if (base->type == LARGE)
		base->large = zoneList;
}

void	*malloc_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_ptr;
	unsigned char	*src_ptr;
	size_t			i;

	dst_ptr = (unsigned char *)dst;
	src_ptr = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		*dst_ptr = *src_ptr;
		dst_ptr++;
		src_ptr++;
		i++;
	}
	recover_base()->is_realloc = 0;
	return (dst);
}


void 	*malloc(size_t size)
{
	t_base 					*base;
	t_zone 					*zoneList;
	void 					*addr;
	int 					i;

	i 						= 0;
	printf("In malloc : %zu octets.\n", size);
	base 					= recover_base();
	base->type 				= size < TINY_BLOCK ? TINY : size < SMALL_BLOCK  ? SMALL : LARGE;
	zoneList 				= (base->type == TINY ? base->tiny :
								base->type == SMALL ? base->small : base->large);
	while (zoneList)
	{
		if (zoneList->next == NULL || zoneList->nbrBlockUsed < zoneList->nbrBlock)
			break;
		zoneList = zoneList->next;
	}
	if (!zoneList || (zoneList && zoneList->nbrBlockUsed > zoneList->nbrBlock))
	{
		printf("Création de la première zone.\n");
		zoneList 			= select_zone();\
		zoneList 			= create_zone(size);
		save_zone(base, zoneList);
	}
	else if (zoneList && zoneList->nbrBlockUsed == zoneList->nbrBlock) 
	{
		printf("Ajout d'une zone \n");
		zoneList->next 		= create_zone(size);
		zoneList  			= zoneList->next;
	}
	addr 					= zoneList->addr;
	while (i++ < zoneList->nbrBlock)
	{
		if (*(int*)addr == 0)
		{
			*(int*)addr 	= size;
			addr 			+= sizeof(int);
			if (recover_base()->is_realloc == 1)
			{
				printf("In malloc, copy realloc\n");
				addr = malloc_memcpy(recover_base()->realloc_src, addr, recover_base()->realloc_size); // acheck
			}
			zoneList->nbrBlockUsed++;
			break;
		}
		else
		{

			addr	+= base->type == TINY ?  (sizeof(int)) + TINY_BLOCK :
						base->type == SMALL ? (sizeof(int)) + SMALL_BLOCK :
							(sizeof(int)) + sizeof(LARGE);
		}
	}
	return (addr);
}