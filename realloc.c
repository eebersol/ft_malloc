/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/27 14:36:04 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

void			*modify_base(void *ptr, size_t new_size)
{
	t_base 				*base;

	base 					= recover_base();
	base->type 				= base->realloc_type; 
	base->realloc_src 		= ptr + sizeof(int);
	base->realloc_new_zone 	= 1; // Add
	base->is_realloc 		= 1;
	// printf("Realloc src : %p\n", base->realloc_src);
	show_alloc_mem();
	free(ptr+sizeof(int));
	show_alloc_mem();
	return(malloc(new_size));
}

void			*browse_zone_realloc(t_zone *zone, void *old_ptr, size_t new_size, int flag)
{
	void 		*ptr;
	int 		i;

	while (zone)
	{
		i = 0;
		ptr = zone->addr;
		// printf("Parcours zone, nbr_block : %zu\n", zone->nbr_block);
		while (i++ < zone->nbr_block)
		{	
			if (flag == 2 && ptr + sizeof(int) == old_ptr)
			{
				if (new_size < *(int*)ptr)
				{
					printf("LALA\n");
					*(int*)ptr = new_size;
					return (ptr + sizeof(int));
				}
			}
			if (ptr + sizeof(int) == old_ptr && flag == 1)
			{
				// printf("Realloc no need, realloc\n");
				*(int*)ptr = new_size;
				return (ptr + sizeof(int));
			}
			else if  (ptr + sizeof(int) == old_ptr && flag != 0)
			{
				// printf("Realloc need, malloc -- new_size %zu\n", new_size);
				return (modify_base(ptr, new_size));
			}
			ptr += get_size_type(zone->type) + sizeof(int);
		}
		if (zone->next == NULL)
			break;
		zone = zone->next;
	}
	// printf("Not found\n");
	return (NULL);
}

void			*find_old_alloc(t_base *base, void *ptr, size_t new_size)
{
	t_zone 	*tmp_zone;
	void 	*old_ptr;
	int 	flag;

	flag = 0;
	old_ptr = NULL;
	if (base->tiny && count_len_zone(base->tiny) != 0)
	{
		// printf("Realloc search in TINY zone.\n");
		flag 		= base->realloc_type == TINY ? 1 : 0; 
		tmp_zone 	= base->tiny;
		old_ptr 	= browse_zone_realloc(tmp_zone, ptr, new_size, flag);
		if (base->realloc_new_zone == 1)
			return (old_ptr);
	}
	if (!old_ptr && base->small && count_len_zone(base->small) != 0)
	{
		// printf("Realloc search in SMALL zone. %p\n", ptr);
		flag 		= base->realloc_type == SMALL ? 1 : 0; 
		tmp_zone 	= base->small;
		old_ptr 	= browse_zone_realloc(tmp_zone, ptr, new_size, flag);
		if (base->realloc_new_zone == 1)
			return (old_ptr);		
	}
	if (!old_ptr && base->large && count_len_zone(base->large) != 0)
	{
		// printf("Realloc search in LARGE zone. %p\n", ptr);
		flag 		= base->realloc_type == LARGE ? 2 : 0; 
		tmp_zone 	= base->large;
		old_ptr 	= browse_zone_realloc(tmp_zone, ptr, new_size, flag);
		if (base->realloc_new_zone == 1)
			return (old_ptr);		
	}
	return (old_ptr);
}

void			*realloc(void *ptr, size_t size)
{
	t_base 				*base;
	void 				*old_addr;


	printf("In realloc :  %zu octets. %p\n", size, ptr);
	if (size == 0 || !ptr)
	{
		return (NULL);
	}
	base 				= recover_base();
	base->realloc_size = size;
	base->realloc_type 	= get_type(size);
	old_addr 			= find_old_alloc(base, ptr, size);
	return (old_addr);
}
