/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/28 14:03:40 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

void	del_zone(t_zone **zone, int at, int block_size, int nbr_block)
{
	t_zone	*tmp;
	t_zone	*prev;
	int		count;

	tmp = *zone;
	prev = NULL;
	count = 0;
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
		block_size = block_size == 0 ?
			*(int*)(&zone[0] + sizeof(t_zone)) : block_size;
		munmap(&zone,
			(sizeof(t_zone)) + ((sizeof(int) + block_size) * nbr_block));
	}
}

t_zone	*browse_zone(t_zone *zone)
{
	t_zone	*tmp_zone;
	int		i;
	int		block_size;

	i = 0;
	tmp_zone = zone;
	while (tmp_zone)
	{
		block_size = get_size_type(tmp_zone->type);
		if (tmp_zone->nbr_block_used == 0)
		{
			del_zone(&zone, i, block_size, tmp_zone->nbr_block);
			tmp_zone = zone;
			if (count_len_zone(zone) != 0)
				browse_zone(tmp_zone);
			else
				return (NULL);
			i = 0;
		}
		if (tmp_zone->next == NULL)
			break ;
		tmp_zone = tmp_zone->next;
		i++;
	}
	return (zone);
}

void	verify_zone(t_base *base)
{
	t_zone	*memory_tmp;

	memory_tmp = base->memory;
	if (memory_tmp)
		base->memory = browse_zone(memory_tmp);
}

void	check_zone(t_zone *zone, void *ptr)
{
	t_zone	*tmp_zone;
	void	*begin;
	int		i;
	int		block_size;

	tmp_zone = zone;
	begin = tmp_zone->addr;
	while (tmp_zone)
	{
		i = 0;
		block_size = get_size_type(tmp_zone->type);
		begin = tmp_zone->addr;
		while (i++ < (int)tmp_zone->nbr_block)
		{
			if (begin + sizeof(int) == ptr)
			{
				tmp_zone->nbr_block_used--;
				*(int*)begin = 0;
			}
			begin += block_size + sizeof(int);
		}
		if (tmp_zone->next == NULL)
			break ;
		tmp_zone = tmp_zone->next;
	}
}

void	free(void *ptr)
{
	t_base	*base;

	base = recover_base();
	if (ptr != NULL)
	{
		check_zone(base->memory, ptr);
		verify_zone(base);
	}
}
