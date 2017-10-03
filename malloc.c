/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/28 16:03:05 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

void	*find_place(t_base *base, t_zone *zone, size_t size)
{
	void	*addr;
	int		i;

	i = 0;
	addr = zone->addr;
	while (i++ < (int)zone->nbr_block)
	{
		if ((*(int*)addr == 0 && base->is_realloc == 0)
			|| (base->is_realloc == 1 && base->realloc_type == zone->type
				&& *(int*)addr == 0))
		{
			*(int*)addr = (int)size;
			addr += sizeof(int);
			if (base->is_realloc == 1)
			{
				addr = malloc_memcpy(addr, base->realloc_src, size);
			}
			zone->nbr_block_used++;
			return (addr);
		}
		else
			addr += get_size_type(zone->type) + sizeof(int);
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
		if (i == strlen(src))
			break ;
		dst_ptr++;
		src_ptr++;
		i++;
	}
	recover_base()->is_realloc = 0;
	return (dst);
}

t_zone	*get_last_zone(t_zone *zone, t_base *base, size_t size)
{
	base->type = get_type(size);
	while (zone)
	{
		if (zone->next == NULL || (zone->nbr_block_used < zone->nbr_block
				&& zone->type == base->type))
			break ;
		zone = zone->next;
	}
	return (zone);
}

void	*malloc(size_t size)
{
	t_base	*base;
	t_zone	*zone;

	if (size == 0)
		return (NULL);
	base = recover_base();
	zone = base->memory;
	zone = get_last_zone(zone, base, size);
	if (!zone || (zone && (zone->nbr_block_used > zone->nbr_block)))
	{
		zone = create_zone(size);
		base->memory = zone;
	}
	else if ((zone && (zone->nbr_block_used == zone->nbr_block
		|| get_type(size) != zone->type)) || (base->is_realloc == 1
			&& base->type != zone->type))
	{
		zone->next = create_zone(size);
		zone = zone->next;
	}
	return (find_place(base, zone, size));
}
