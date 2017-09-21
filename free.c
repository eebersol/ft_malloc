/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/21 15:40:41 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"


void	del_zone(t_zone **zone, int at, int block_size, int nbr_block)
{
	t_zone 	*tmp;
	t_zone 	*prev;
	int		count;

	if (!zone || !(*zone))
		return ;
	tmp 	= *zone;
	prev 	= NULL;
	count	= 0;
	while (count != at && tmp->next != NULL)
	{
		prev = tmp;
		tmp = tmp->next;
		count++;
	}
	if (count == at)
	{
		if (prev)
			prev->next = tmp->next;
		else
			*zone = tmp->next;
		block_size = block_size == 0 ? *(int*)(&zone[0] + sizeof(t_zone)) : block_size;
		munmap(&zone,  (sizeof(t_zone)) + ((sizeof(int) + block_size) * nbr_block));
	}
}


t_zone 	*browse_zone(t_zone *zone, int block_size)
{
	t_zone 		*tmp_zone;
	int 		i;

	i 			= 0;
	tmp_zone 	= zone;
	while (tmp_zone)
	{
		if (tmp_zone->nbrBlockUsed == 0)
		{
			del_zone(&zone, i,  block_size, tmp_zone->nbrBlock);
			tmp_zone = zone;
			if (ft_lstcount(zone) != 0)
				browse_zone(tmp_zone, block_size);
			else
				return (NULL);
			i = 0;
		}
		if (tmp_zone->next == NULL)
			break;
		tmp_zone = tmp_zone->next;
		i++;
	}
	return (zone);
}

void 	verify_zone(t_base *base)
{
	t_zone 		*tiny_tmp;
	t_zone 		*small_tmp;
	t_zone 		*large_tmp;

	tiny_tmp 	= base->tiny;
	small_tmp 	= base->small;
	large_tmp 	= base->large;

	if (tiny_tmp)
		base->tiny 	= browse_zone(tiny_tmp, TINY_BLOCK);
	if (small_tmp)
		base->small = browse_zone(small_tmp, SMALL_BLOCK);
	if (large_tmp)
		base->large = browse_zone(large_tmp, 0);
}

int 	check_zone(t_zone *zone, void *ptr, int size_block)
{
	t_zone 		*tmpZone;
	void 		*begin;
	int 		i;

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
				tmpZone->nbrBlockUsed--;
				*(int*)begin  = 0;
				return (1);
			}
			begin += size_block + sizeof(int);
		}
		if (tmpZone->next == NULL)
			break;
		tmpZone = tmpZone->next;
	}
	// zone = tmpZone; Norme vérifier que ce soit useless
	return (0);
}

void	free(void *ptr)
{
	t_base 	*base;

	base = recover_base();

	if (ptr != NULL)
	{
		check_zone(base->tiny, ptr, TINY_BLOCK) == 1 ? 0 :
			check_zone(base->small, ptr, SMALL_BLOCK) == 1 ? 0 :
				check_zone(base->large, ptr, 0);
		verify_zone(base);
	}
}
