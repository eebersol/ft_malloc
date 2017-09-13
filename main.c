/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/13 14:55:10 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"


static int		ft_lstcount(t_block *lst)
{
	int		i;
	t_block	*elem;

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


void 	*ft_malloc (size_t size)
{
	t_zone *zone;
	int *allocation;

	zone = recover_zone();
	size += sizeof(size);
	allocation = smap(size);

	*allocation = size;
	return (void*)(&allocation[0]);
}

int main (int ac, char **av)
{
	t_zone 	*zone;
	t_block *begin;
	int i;

	init_zone();
	zone = recover_zone();
	begin = zone->block;
	i = 0;
	zone->type = TINY;
	printf("Begin, First Block : %p -- %d\n", begin->addr, begin->free);
	while (i < 8) 
	{
		i++;
		begin->next = create_block(1000);
		begin = begin->next;
		printf("Block xx : %p -- %d\n", begin->addr, begin->free);
	}
	printf("Size : begin : %d zone->block : %d\n", ft_lstcount(begin), ft_lstcount(zone->block));
	show_alloc_meme();

}