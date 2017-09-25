/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/25 13:06:55 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

void 	*find_place(t_base *base, t_zone *zone, size_t size)
{
	void 	*addr;
	int 	i;

	i 		= 0;
	addr 	= zone->addr;
	while (i++ < zone->nbr_block)
	{
		if (*(int*)addr == 0)
		{
			*(int*)addr 	= size;
			addr 			+= sizeof(int);
			if (base->is_realloc == 1)
			{
				// printf("In malloc, copy realloc\n");
				addr = malloc_memcpy(base->realloc_src, addr, size);
			}
			zone->nbr_block_used++;
			break;
		}
		else
			addr	+= get_size_type(base->type) + sizeof(int);
	}
	return (addr);
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
	t_base 			*base;
	t_zone 			*zone;

	// printf("In malloc : %zu octets.\n", size);
	base 			= recover_base();
	base->type 		= get_type(size);
	zone 			= get_zone();
	while (zone)
	{
		if (zone->next == NULL || zone->nbr_block_used < zone->nbr_block)
			break;
		zone = zone->next;
	}
	if (!zone || (zone && zone->nbr_block_used > zone->nbr_block))
	{
		// printf("Création de la première zone.\n");
		zone 		= create_zone(size);
		save_zone(base, zone);
	}
	else if (zone && zone->nbr_block_used == zone->nbr_block) 
	{
		// printf("Ajout d'une zone \n");
		zone->next 	= create_zone(size);
		zone  		= zone->next;
	}
	return(find_place(base, zone, size));
}
