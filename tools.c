/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/28 16:07:46 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

void	*smap(size_t len)
{
	size_t	multiple;

	multiple = (len / PAGE_SIZE) + 1;
	len = multiple * PAGE_SIZE;
	return (mmap(NULL, len, FLAG_PROT, FLAG_MAP, -1, 0));
}

t_zone	*fix_zone_size(size_t size_total, size_t size)
{
	t_zone_type type;

	type = get_type(size);
	if (type == TINY)
		return ((t_zone *)smap((sizeof(t_zone))
			+ ((sizeof(int) + TINY_BLOCK) * size_total)));
	else if (type == SMALL)
		return ((t_zone *)smap((sizeof(t_zone))
			+ ((sizeof(int) + SMALL_BLOCK) * size_total)));
	else
		return ((t_zone *)smap((sizeof(t_zone))
			+ ((sizeof(int) + size))));
}

t_zone	*create_zone(size_t size)
{
	t_zone	*zone;
	t_base	*base;
	size_t	size_total;
	void	*begin;
	int		i;

	i = 0;
	size_total = get_nbr_block(size);
	base = recover_base();
	zone = fix_zone_size(size_total, size);
	zone->type = get_type(size);
	zone->nbr_block_used = 0;
	zone->addr = &zone[0] + sizeof(t_zone);
	zone->nbr_block = zone->type == LARGE ? 1 : size_total;
	zone->next = NULL;
	begin = zone->addr;
	while (i++ < (int)zone->nbr_block)
	{
		*(int*)begin = 0;
		begin += sizeof(int) + get_size_type(zone->type);
	}
	return (zone);
}

int		count_len_zone(t_zone *lst)
{
	int		i;
	t_zone	*elem;

	i = 0;
	elem = lst;
	if (elem)
	{
		while (elem)
		{
			i++;
			elem = elem->next;
		}
	}
	return (i);
}
