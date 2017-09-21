/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/20 14:35:17 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

// peut-on mettre un ternaire dans un call de fonction pour set un des arg
// realloc doit reallouer au meme endroit si cest possible
void 	*set_new_size(t_zone *zone, size_t size, t_zone_type type)
{
	t_zone *tmpZone;
	void 	*begin;
	int 	jump;
	int 	i;

	tmpZone 	= zone;
	begin 		= tmpZone->addr;
	jump 		= type == 0 ? TINY_BLOCK : type == 1 ? SMALL_BLOCK : 0;
	while (tmpZone)
	{
		i 		= 0;
		begin 	= tmpZone->addr;
		while (i++ < tmpZone->nbrBlock)
		{
			if (*(int*)begin == 0)
			{
				tmpZone->nbrBlockUsed++;
				*(int*)begin = (int)size;
				return (begin + sizeof(int));
			}
			begin += sizeof(int) + jump;
		}
		if (tmpZone->next == NULL)
			break;
		tmpZone = tmpZone->next;
	}
	return (NULL);
}

void 	*get_content(void *ptr, size_t size)
{
	t_base 	*base;
	void 	*content;
	int 	i;
	int 	len;

	base 				= recover_base();
	i 					= 0;
	len 				= *(int*)ptr > size ? size : *(int*)ptr; 
	base->last_realloc 	= ptr;
	ptr 				+= sizeof(int);
	while (i++ < len)
	{
		content = ptr;
		content += 1;
		ptr += 1;
	}
	base->last_realloc_content 	= content;
	base->realloc_flag = 1;
	return (content);
}

int 	find_ptr(t_zone *zone, void *ptr, int jump, size_t size)
{
	t_zone *tmpZone;
	void 	*begin;
	int 	i;

	tmpZone 	= zone;
	begin 		= tmpZone->addr;
	while (tmpZone)
	{
		i 		= 0;
		begin 	= tmpZone->addr;
		while (i++ < tmpZone->nbrBlock)
		{
			if (begin + sizeof(int) == ptr)
			{
				printf("ICI\n");
				get_content(begin, size);
				return (*(int*)(begin));
			}
			begin += jump + sizeof(int);
		}
		if (tmpZone->next == NULL)
			break;
		tmpZone = tmpZone->next;
	}
	return (0);
}

void 	*realloc(void *ptr, size_t size)
{
	t_base 		*base;
	t_zone 		*tmpZone;
	t_zone_type newType;
	t_zone_type oldType;
	int 		actual_size;

	base 		= recover_base();
	actual_size = find_ptr(base->tiny, ptr, TINY_BLOCK, size);
	actual_size = actual_size == 0 ? find_ptr(base->small, ptr, SMALL_BLOCK, size) : actual_size;
	actual_size = actual_size == 0 ? find_ptr(base->large, ptr, 0, size) : actual_size;
	oldType 	= actual_size < TINY_BLOCK ? TINY : actual_size < SMALL ? SMALL : LARGE;
	newType 	= size < TINY_BLOCK ? TINY : size < SMALL ? SMALL : LARGE;
	if (oldType == newType)
	{
		ptr 		= base->last_realloc;
		ptr 		-= sizeof(int);
		*(int*)ptr 	= size;
		return (ptr + sizeof(int));
	}
	else
	{
		printf("MALLOC\n");
		tmpZone 	= newType == 0 ? base->tiny : newType == 1 ? base->small : base->large;
		ptr 		= set_new_size(tmpZone, size, newType);
		if (ptr == NULL)
			ptr 	= malloc(size);
		return (ptr);
	}
}