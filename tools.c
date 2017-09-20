/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/20 11:08:36 by eebersol         ###   ########.fr       */
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
	t_global_ref 	*ref;

	base 			= recover_base();
	ref 			= recover_global_ref();
	if (ref->type == TINY)
		return (base->tiny);
	else if (ref->type == SMALL)
		return (base->small);
	else if (ref->type == LARGE)
		return (base->large);
	else
		return (NULL);
}

size_t 	get_size_total(size_t size)
{
	t_global_ref 	*ref;
	int 			i;
	int 			sizeTotal;


	i 				= 0;
	ref 			= recover_global_ref();
	sizeTotal = 0;
	sizeTotal 		= ref->type == TINY ?  (sizeof(t_zone)) + ((sizeof(int) + TINY_BLOCK) * 100) :
						ref->type == SMALL ? (sizeof(t_zone)) + ((sizeof(int) + SMALL_BLOCK) * 100) :
							(sizeof(t_zone)) + ((sizeof(int) + size));
	// if (ref->type == TINY)
	// 	sizeTotal 	= (sizeof(t_zone)) + ((sizeof(int) + TINY_BLOCK) * 100);
	// else if (ref->type == SMALL)
	// 	sizeTotal 	= (sizeof(t_zone)) + ((sizeof(int) + SMALL_BLOCK) * 100);
	// else if (ref->type == LARGE)
	// 	sizeTotal 	= (sizeof(t_zone)) + ((sizeof(int) + LARGE_ZONE));
	while (i * PAGE_SIZE < sizeTotal)
		i++;
	i 				*= PAGE_SIZE;
	sizeTotal 		= ref->type == TINY ?  i/TINY_BLOCK : ref->type == SMALL ? i/SMALL_BLOCK :  i/LARGE;
	// if (ref->type == TINY)
	// 	sizeTotal = i/TINY_BLOCK;
	// else if (ref->type == SMALL)
	// 	sizeTotal = i/SMALL_BLOCK;
	// else if (ref->type == LARGE)
	// 	sizeTotal = i/LARGE;
	return (sizeTotal);
}

t_zone 	*create_zone(size_t size)
{
	t_zone 				*zone;
	t_global_ref 		*ref;
	size_t 				sizeTotal;
	void 				*begin;
	int 				i;

	i 					= 0;
	ref 				= recover_global_ref();
	sizeTotal 			= get_size_total(size);

	zone 	 			= ref->type == TINY ?  (t_zone *)smap((sizeof(t_zone)) + ((sizeof(int) + TINY_BLOCK) * sizeTotal)) :
							ref->type == SMALL ? (t_zone *)smap((sizeof(t_zone)) + ((sizeof(int) + SMALL_BLOCK) * sizeTotal)) :
								(t_zone *)smap((sizeof(t_zone)) + ((sizeof(int) + size)));
	// if (ref->type == TINY)
	// 	zone 	= (t_zone *)smap((sizeof(t_zone)) + ((sizeof(int) + TINY_BLOCK) * sizeTotal));
	// else if (ref->type == SMALL)
	// {
	// 	printf("Creation szone SMALL\n");
	// 	zone = (t_zone *)smap((sizeof(t_zone)) + ((sizeof(int) + SMALL_BLOCK) * sizeTotal));
	// }
	// else if (ref->type == LARGE)
	// 	zone = (t_zone *)smap((sizeof(t_zone)) + ((sizeof(int) + LARGE_ZONE)));
	// else
	// 	return (NULL);

	zone->nbrBlockUsed = 0;
	zone->addr 			= &zone[0] + sizeof(t_zone);
	zone->nbrBlock 		= ref->type == LARGE ? 1 : sizeTotal;
	zone->next 			= NULL;
	begin 				= zone->addr; // Faut-il ajouter +1 pour sortir de la zone

	while (i < zone->nbrBlock)
	{
		*(int*)begin = 0;
		begin 			+= ref->type == TINY ?  (sizeof(int)) + TINY_BLOCK :
							ref->type == SMALL ? (sizeof(int)) + SMALL_BLOCK :
								(sizeof(int)) + sizeof(LARGE);
		// if (ref->type == TINY)
		// 	begin += (sizeof(int)) + TINY_BLOCK;
		// else if (ref->type == SMALL)
		// 	begin += (sizeof(int)) + SMALL_BLOCK;
		// else if (ref->type == LARGE)
		// 	begin += (sizeof(int)) + sizeof(LARGE);
		i++;
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