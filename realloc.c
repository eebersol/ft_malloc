/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/28 15:06:16 by eebersol         ###   ########.fr       */
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
	free(ptr+sizeof(int));
	return(malloc(new_size));
}

void			*browse_zone_realloc(t_zone *zone, void *old_ptr, size_t new_size, int flag)
{
	void 		*ptr;
	int 		i;
	int 		limit;

	while (zone)
	{
		i = 0;
		ptr = zone->addr;
		while (i++ < zone->nbr_block)
		{	
			printf("FLAG : %d\n",flag );
			if (ptr + sizeof(int) == old_ptr)
			{
				limit = 0;
				if (new_size < *(int*)ptr && new_size > SMALL_BLOCK)
				{
					printf("no nedd malloc\n");
					*(int*)ptr = new_size;
					return (ptr + sizeof(int));
				}
				else
				{
					printf("need malloc -- realloc_type %d\n", recover_base()->realloc_type);
					return (modify_base(ptr, new_size));
				}
			}
			if (ptr + sizeof(int) == old_ptr && flag == 0)
			{
				*(int*)ptr = new_size;
				return (ptr + sizeof(int));
			}
			else if  (ptr + sizeof(int) == old_ptr && flag != 1)
			{
				return (modify_base(ptr, new_size));
			}
			ptr += get_size_type(zone->type) + sizeof(int);
		}
		if (zone->next == NULL)
			break;
		zone = zone->next;
	}
	printf("Not found\n");
	return (NULL);
}

void			*find_old_alloc(t_base *base, void *ptr, size_t new_size)
{
	t_zone 	*tmp_zone;
	void 	*old_ptr;
	int 	flag;

	flag 	= 0;
	old_ptr = NULL;
	if (base->memory && count_len_zone(base->memory) != 0)
	{
		flag 		= base->realloc_type == TINY ? 0 : base->realloc_type == SMALL ? 1 : 2;
		tmp_zone 	= base->memory;
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
		return (NULL);
	base 				= recover_base();
	base->realloc_size 	= size;
	base->realloc_type 	= get_type(size);
	old_addr 			= find_old_alloc(base, ptr, size);
	return (old_addr);
}
