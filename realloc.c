/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/28 16:22:50 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

void	*modify_base(void *ptr, size_t new_size)
{
	t_base	*base;

	base = recover_base();
	base->type = base->realloc_type;
	base->realloc_src = ptr + sizeof(int);
	base->realloc_new_zone = 1;
	base->is_realloc = 1;
	free(ptr + sizeof(int));
	return (malloc(new_size));
}

void	*browse_zone_realloc(t_zone *zone, void *old_ptr,
										size_t new_size, void *ptr)
{
	int i;

	while (zone)
	{
		i = 0;
		ptr = zone->addr;
		while (i++ < (int)zone->nbr_block)
		{
			if (ptr + sizeof(int) == old_ptr)
			{
				if (recover_base()->realloc_type == zone->type)
				{
					*(int*)ptr = new_size;
					return (ptr + sizeof(int));
				}
				else
					return (modify_base(ptr, new_size));
			}
			ptr += get_size_type(zone->type) + sizeof(int);
		}
		if (zone->next == NULL)
			break ;
		zone = zone->next;
	}
	return (NULL);
}

void	*find_old_alloc(t_base *base, void *ptr, size_t new_size)
{
	t_zone	*tmp_zone;
	void	*old_ptr;
	int		i;
	void	*new_ptr;

	old_ptr = NULL;
	new_ptr = NULL;
	i = 0;
	if (base->memory && count_len_zone(base->memory) != 0)
	{
		tmp_zone = base->memory;
		old_ptr = browse_zone_realloc(tmp_zone, ptr, new_size, new_ptr);
		if (base->realloc_new_zone == 1)
			return (old_ptr);
	}
	return (old_ptr);
}

void	*realloc(void *ptr, size_t size)
{
	t_base	*base;
	void	*old_addr;

	if (size != 0 && !ptr)
		return (malloc(size));
	base = recover_base();
	base->realloc_size = size;
	base->realloc_type = get_type(size);
	old_addr = find_old_alloc(base, ptr, size);
	return (old_addr);
}
