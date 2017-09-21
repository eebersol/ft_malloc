/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_true.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/21 14:56:27 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

t_zone_type 	get_type(size_t size)
{
	return (size < TINY_BLOCK ? TINY : size < SMALL_BLOCK ? SMALL : LARGE);
}

size_t 		get_size_type(t_zone_type type)
{
	printf("type : %d\n", type);
	return (type == TINY ? TINY_BLOCK : type == SMALL ? SMALL_BLOCK : 0);
}


void			*browse_zone_realloc(t_zone *zone, void *old_ptr, size_t new_size, int flag)
{
	t_base 		*base;
	void 		*ptr;
	int 		i;

	base = recover_base();
	while (zone)
	{
		i = 0;
		ptr = zone->addr;
		while (i++ < zone->nbrBlock)
		{	
			if (ptr + sizeof(int) == old_ptr && flag == 1)
			{
				printf("Realloc no need, realloc\n");
				*(int*)ptr = new_size;
				return (ptr + sizeof(int));
			}
			else if  (ptr + sizeof(int) == old_ptr && flag == 0)
			{
				printf("Realloc need, malloc -- new_size %zu\n", new_size);
				base->realloc_src = ptr + sizeof(int);
				base->realloc_size = new_size;
				base->is_realloc = 1;
				base->type = base->realloc_type; 
				free(ptr+sizeof(int));
				return (malloc(new_size));
			}
			ptr += get_size_type(zone->type) + sizeof(int);
		}
		if (zone->next == NULL)
		{
			printf("BREAK\n");
			break;
		}
		zone = zone->next;
	}
	return (NULL);
}

void 			*find_old_alloc(t_base *base, void *ptr, size_t new_size)
{
	t_zone 	*tmp_zone;
	void 	*old_ptr;
	int 	flag;

	flag = 0;
	old_ptr = NULL;
	if (base->tiny && ft_lstcount(base->tiny) != 0)
	{
		printf("Realloc search in TINY zone.\n");
		flag 		= base->realloc_type == TINY ? 1 : 0; 
		tmp_zone 	= base->tiny;
		old_ptr 	= browse_zone_realloc(tmp_zone, ptr, new_size, flag);
		if (base->realloc_new_zone == 1)
			return (old_ptr);
	}
	if (!old_ptr && base->small && ft_lstcount(base->small) != 0)
	{
		printf("Realloc search in SMALL zone. %p\n", ptr);
		flag 		= base->realloc_type == SMALL ? 1 : 0; 
		tmp_zone 	= base->small;
		old_ptr 	= browse_zone_realloc(tmp_zone, ptr, new_size, flag);
		if (base->realloc_new_zone == 1)
			return (old_ptr);		
	}
	return (old_ptr);
}

void 			*realloc(void *ptr, size_t size)
{
	t_base 				*base;
	void 				*old_addr;

	if (size == 0 || !ptr)
		return (NULL);
	printf("In realloc :  %zu octets.\n", size);
	base 				= recover_base();
	base->realloc_type 	= get_type(size);
	old_addr 			= find_old_alloc(base, ptr, size);
	return (old_addr);


}