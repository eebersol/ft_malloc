/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/18 11:23:43 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void 	*smap(size_t len)
{
	size_t multiple;

	multiple = (len / PAGE_SIZE) + 1;
	len = multiple * PAGE_SIZE;
	printf("SMAP : %zu\n", len);
	return (mmap(NULL, len, PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0));
}

t_zone *select_zone()
{
	t_base *base;
	t_global_ref *ref;

	base = recover_base();
	ref = recover_global_ref();
	if (ref->type == TINY)
	{
		printf("Tinny zone :\n");
		return (base->tiny);
	}
	else if (ref->type == SMALL)
	{
		printf("Small zone :\n");
		return (base->small);

	}
	else if (ref->type == LARGE)
	{
		printf("Large zone :\n");
		return (base->large);
	}
	else
	{
		printf("undefined type\n");
		return (NULL);
	}
}

size_t 	get_size_total()
{
	t_global_ref *ref;
	int 	i;
	int 	sizeTotal;


	i = 0;
	ref = recover_global_ref();
	sizeTotal = 0;
	if (ref->type == TINY)
		sizeTotal = (sizeof(t_zone)) + ((sizeof(int) + TINY_BLOCK) * 100);
	else if (ref->type == SMALL)
		sizeTotal = (sizeof(t_zone)) + ((sizeof(int) + SMALL_BLOCK) * 100);
	else if (ref->type == LARGE)
		sizeTotal = (sizeof(t_zone)) + ((sizeof(int) + LARGE_ZONE));

	while (i * PAGE_SIZE < sizeTotal)
		i++;
	i = i * PAGE_SIZE;

	if (ref->type == TINY)
		sizeTotal = i/TINY_BLOCK;
	else if (ref->type == SMALL)
		sizeTotal = i/SMALL_BLOCK;
	else if (ref->type == LARGE)
		sizeTotal = i/LARGE;
	return (sizeTotal);
}

t_zone 	*create_zone()
{
	t_zone 			*zone;
	t_global_ref 	*ref;
	size_t 			sizeTotal;
	void 			*begin;
	void 			*ptr;
	int 			i;

	i = 0;
	ref = recover_global_ref();
	sizeTotal = get_size_total();
	printf("NBR BLOCK : %zu\n", sizeTotal);
	if (ref->type == TINY)
		zone = (t_zone *)smap((sizeof(t_zone)) + ((sizeof(int) + TINY_BLOCK) * sizeTotal));
	else if (ref->type == SMALL)
		zone = (t_zone *)smap((sizeof(t_zone)) + ((sizeof(int) + SMALL_BLOCK) * sizeTotal));
	else if (ref->type == LARGE)
		zone = (t_zone *)smap((sizeof(t_zone)) + ((sizeof(int) + LARGE_ZONE)));

	zone->addr 	= (void*)&zone;
	zone->nbrBlock = sizeTotal;
	zone->next 	= NULL;
	ptr = zone->addr;
	printf("Ptr : %p\n", ptr);
	begin = ptr + (sizeof(zone));
	printf("Begin : %p\n", begin);
	while (i < zone->nbrBlock)
	{
		printf("Begin :: %p\n", begin);
		*(int*)begin = 0;
		// Set begin a 0 pour indiquer que le block est libre.
		printf("Begin :: %p\n", begin);
		if (ref->type == TINY)
			begin += (sizeof(int)) + TINY_BLOCK;
		else if (ref->type == SMALL)
			begin += (sizeof(int)) + SMALL_BLOCK;
		else if (ref->type == LARGE)
			begin += (sizeof(int)) + LARGE;
		printf("End :: %p\n", begin);
		// add +1 pour ne pas que les cases memoire s'enjambe
		i++;
		printf("[%d] < [%zu]\n", i, zone->nbrBlock);
	}
	return (zone);
}


int		ft_lstcountzone(t_zone *lst)
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