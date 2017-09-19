/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/19 16:26:15 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

void 	save_zone(t_base *base, t_zone *zoneList, t_global_ref *ref)
{
	if (ref->type == TINY)
		base->tiny = zoneList;
	else if (ref->type == SMALL)
		base->small = zoneList;
	else if (ref->type == LARGE)
		base->large = zoneList;
}


void 	*malloc(size_t size)
{
	t_global_ref 			*ref;
	t_base 					*base;
	t_zone 					*zoneList;
	int 					i;
	void 					*addr;

	i 						= 0;
	size 					+= (sizeof(size));
	ref 					= recover_global_ref();
	base 					= recover_base();
	ref->type 				= size < TINY_BLOCK ? TINY : size < SMALL_BLOCK  ? SMALL : LARGE;
	zoneList 				= (ref->type == TINY ? base->tiny :
								ref->type == SMALL ? base->small : base->large);
	while (zoneList)
	{
		if (zoneList->next == NULL || zoneList->nbrBlockUsed < zoneList->nbrBlock)
			break;
		zoneList = zoneList->next;
	}
	if (!zoneList || (zoneList && zoneList->nbrBlockUsed > zoneList->nbrBlock))
	{
		printf("Création de la première zone.\n");
		zoneList 			= select_zone();
		zoneList 			= create_zone(size);
		save_zone(base, zoneList, ref);	
	}
	else if (zoneList && zoneList->nbrBlockUsed == zoneList->nbrBlock) 
	{
		printf("Ajout d'une zone \n");
		zoneList->next 		= create_zone(size);
		zoneList  			= zoneList->next;
	}
	addr 					= zoneList->addr;
	while (i < zoneList->nbrBlock)
	{
		if (*(int*)addr == 0)
		{
			*(int*)addr 	= size;
			addr 			+= sizeof(int);
			zoneList->nbrBlockUsed++;
			break;
		}
		else
		{

			addr			+= ref->type == TINY ?  (sizeof(int)) + TINY_BLOCK :
								ref->type == SMALL ? (sizeof(int)) + SMALL_BLOCK :
									(sizeof(int)) + sizeof(LARGE);
			// if (ref->type == TINY)
			// 	addr 	+= (sizeof(int)) + TINY_BLOCK;
			// else if (ref->type == SMALL)
			// 	addr 	+= (sizeof(int)) + SMALL_BLOCK;
			// else if (ref->type == LARGE)
			// 	addr += (sizeof(int)) + sizeof(LARGE);
		}
		i++;
	}
	return (addr);
}