/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/28 16:06:30 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/malloc.h"

void printf_info_zone(void *ptr, int i, t_zone_type type)
{
	ft_putstr("\n- n°");
	ft_putnbr(i);
	type == TINY ? ft_putstr(" TINY : ") :
		type == SMALL ? ft_putstr(" SMALL : ") : ft_putstr(" LARGE : ");
	ft_putstr(ft_itohex(ptr));
	ft_putstr("-\n\n");

}

void print_info_block(void *ptr, int i, int size)
{
	ft_putstr("[");
	ft_putnbr(i);
	ft_putstr("] 0x");
	ft_putstr(ft_itohex(ptr + sizeof(int)));
	ft_putstr("- 0x");
	ft_putstr(ft_itohex(ptr + size + sizeof(int)));
	ft_putstr(": ");
	ft_putnbr(size);
	ft_putstr(" octets\n");
}

size_t display_block(t_zone *zone)
{
	void 				*ptr;
	int 				size_total;
	int 				block;
	int 				i;

	size_total 			= 0;
	ptr 				= zone->addr;
	i 					= 0;
	while (i++ < zone->nbr_block)
	{
		if (*(int*)ptr != 0)
		{
			block 		= zone->type == TINY ? TINY_BLOCK : 
							zone->type == SMALL ? SMALL_BLOCK : *(int*)ptr;
			print_info_block(ptr, i,  *(int*)ptr);
			ptr 		+= sizeof(int);
			block 		= block == 0 ? *(int*)ptr : block;
			ptr 		+= block;
			size_total 	+= *(int*)ptr;
		}
		else
			ptr 		+= (sizeof(int)) + block;
	}
	return (size_total);
}

int	print_zone(t_zone *zone)
{
	t_zone 	*tmp_zone;
	int 	size_total;
	int 	i;

	i = 0;
	tmp_zone = zone;
	size_total = 0;
	while (tmp_zone && tmp_zone->next != NULL)
	{
		printf_info_zone(tmp_zone->addr, i, tmp_zone->type);
		size_total += display_block(tmp_zone);
		tmp_zone = tmp_zone->next;
		i++;
	}
	return (size_total);
}


void show_alloc_mem()
{
	t_base 		*base;
	t_zone 		*zone;
	size_t 		size_total;

	zone 		= NULL;
	base 		= recover_base();
	size_total 	= 0;
	printf("\n-----------------------------------------------------\n\n");
	printf("Show_alloc_meme : \n\n Len memory  : [%d] \n", count_len_zone(base->memory));
	if (base->memory)
	{
		ft_lst_bubble_sort(base->memory);
		size_total += print_zone(base->memory);
	}
	ft_putstr("\nTotal : ");
	ft_putnbr(size_total);
	ft_putstr(" octets\n\n");
}
