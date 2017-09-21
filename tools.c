/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/21 15:07:08 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void 	*smap(size_t len)
{
	size_t  	multiple;

	multiple 	= (len / PAGE_SIZE) + 1;
	len 		= multiple * PAGE_SIZE;
	// printf("SMAP : %zu\n", len);
	return (mmap(NULL, len, PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0));
}

t_zone *select_zone()
{
	t_base 			*base;

	base 			= recover_base();
	if (base->type == TINY)
		return (base->tiny);
	else if (base->type == SMALL)
		return (base->small);
	else if (base->type == LARGE)
		return (base->large);
	else
		return (NULL);
}

size_t 	get_size_zone(t_zone_type type, size_t size)
{
	return (type == TINY ?  (sizeof(t_zone)) + ((sizeof(int) + TINY_BLOCK) * 100) :
				type == SMALL ? (sizeof(t_zone)) + ((sizeof(int) + SMALL_BLOCK) * 100) :
					(sizeof(t_zone)) + ((sizeof(int) + size)));
}

size_t 	get_nbr_block(size_t size)
{
	t_base			*base;
	int 			nbr_block;
	int 			total_size;


	base 			= recover_base();
	total_size 		= 0;
	nbr_block 		= get_size_zone(base->type, size);
	while (total_size * PAGE_SIZE < nbr_block)
		total_size++;
	total_size 		*= PAGE_SIZE;
	nbr_block 		= base->type == TINY ?  total_size/TINY_BLOCK : base->type == SMALL ? total_size/SMALL_BLOCK :  total_size/LARGE;
	return (nbr_block);
}

t_zone 	*create_zone(size_t size)
{
	t_zone 				*zone;
	t_base 				*base;
	size_t 				sizeTotal;
	void 				*begin;
	int 				i;

	i 					= 0;
	sizeTotal 			= get_nbr_block(size);
	base 				= recover_base();	
	zone 	 			= base->type == TINY ?  (t_zone *)smap((sizeof(t_zone)) + ((sizeof(int) + TINY_BLOCK) * sizeTotal)) :
							base->type == SMALL ? (t_zone *)smap((sizeof(t_zone)) + ((sizeof(int) + SMALL_BLOCK) * sizeTotal)) :
								(t_zone *)smap((sizeof(t_zone)) + ((sizeof(int) + size)));
	zone->nbrBlockUsed = 0;
	zone->addr 			= &zone[0] + sizeof(t_zone);
	zone->nbrBlock 		= base->type == LARGE ? 1 : sizeTotal;
	zone->next 			= NULL;
	zone->type 			= get_type(size);
	begin 				= zone->addr;

	while (i++ < zone->nbrBlock)
	{
		*(int*)begin = 0;
		begin 			+= (base->type == TINY ? TINY_BLOCK : base->type == SMALL ? SMALL_BLOCK : size) + sizeof(int);
	}
	return (zone);
}


int		ft_lstcount(t_zone *lst)
{
	int			i;
	t_zone		*elem;

	i 			= 0;
	elem 		= lst;
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