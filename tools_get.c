/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/28 16:07:58 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

t_zone_type	get_type(size_t size)
{
	if (size < TINY_BLOCK)
		return (TINY);
	else if (size < SMALL_BLOCK)
		return (SMALL);
	else
		return (LARGE);
}

size_t		get_size_type(t_zone_type type)
{
	if (type == TINY)
		return (TINY_BLOCK);
	else if (type == SMALL)
		return (SMALL_BLOCK);
	else
	{
		return (0);
	}
}

size_t		get_size_zone(t_zone_type type, size_t size)
{
	if (type == TINY)
		return ((sizeof(t_zone)) + ((sizeof(int) + TINY_BLOCK) * 100));
	else if (type == SMALL)
		return ((sizeof(t_zone)) + ((sizeof(int) + SMALL_BLOCK) * 100));
	else
		return ((sizeof(t_zone)) + ((sizeof(int) + size)));
}

size_t		get_nbr_block(size_t size)
{
	t_base	*base;
	int		nbr_block;
	int		total_size;

	base = recover_base();
	total_size = 0;
	nbr_block = get_size_zone(base->type, size);
	while (total_size * PAGE_SIZE < nbr_block)
		total_size++;
	total_size *= PAGE_SIZE;
	if (base->type == TINY)
		nbr_block = total_size / TINY_BLOCK;
	else if (base->type == SMALL)
		nbr_block = total_size / SMALL_BLOCK;
	else
		nbr_block = 1;
	return (nbr_block);
}
