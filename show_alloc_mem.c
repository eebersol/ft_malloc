/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/26 20:29:27 by macbook          ###   ########.fr       */
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
	ft_putstr("- 0x"); // pb avec le space
	ft_putstr(ft_itohex(ptr + size + sizeof(int)));
	ft_putstr(": ");
	ft_putnbr(size);
	ft_putstr(" octets\n");
}

size_t display_block(t_zone *zone, t_zone_type type)
{
	void 				*ptr;
	int 				i;
	int 				size;
	int 				size_total;
	int 				block;

	i 					= 0;
	size_total 			= 0;
	ptr 				= zone->addr;
	while (i < zone->nbr_block)
	{
		if (*(int*)ptr != 0)
		{
			size 		= *(int*)ptr;
			block 		= type == TINY ? TINY_BLOCK : 
							type == SMALL ? SMALL_BLOCK : size;
			// printf("TRUE   [%d] %p - %p : %d octets\n",i, ptr  + sizeof(int), ptr + block + sizeof(int), *(int*)ptr);
			print_info_block(ptr, i,  size);
			ptr 		+= sizeof(int);
			block 		= block == 0 ? size : block;
			ptr 		+= block;
			size_total 	+= size;
		}
		else
			ptr 		+= (sizeof(int)) + block;
		i++;
	}
	//printf("size_total : %d\n", size_total);
	return (size_total);
}

int	print_zone(t_zone *zone, t_zone_type type)
{
	t_zone 	*tmp_zone;
	int 	size_total;
	int 	i;

	i = 0;
	tmp_zone = zone;
	size_total = 0;
	while (tmp_zone)
	{
		//printf("BLOCK : %zu\n", zone->nbr_block);
		printf_info_zone(tmp_zone->addr, i, type);
		//printf("BLOCK 2 : %zu\n", zone->nbr_block);
		size_total += display_block(tmp_zone, type);
		if (tmp_zone->next == NULL)
			break ;
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
	int 		jump;
	int 		i;

	zone 		= NULL;
	base 		= recover_base();
	size_total 	= 0;
	i 			= 0;
	jump 		= 0;
	printf("\n-----------------------------------------------------\n\n");
	printf("Show_alloc_meme : \n\n");
	printf("Len tiny  : [%d] \n", count_len_zone(base->tiny));
	printf("Len small : [%d] \n", count_len_zone(base->small));
	printf("Len large : [%d] \n", count_len_zone(base->large));
	printf("\n%p\n", zone->addr);
	if (base)
	{
		size_total += print_zone(base->tiny, TINY);
		size_total += print_zone(base->small, SMALL);
		size_total += print_zone(base->large, LARGE);
	}
	ft_putstr("\nTotal : ");
	ft_putnbr(size_total);
	ft_putstr(" octets\n\n");
//	printf("\nTotal : %lu octets\n", size_total);
//	printf("\n-----------------------------------------------------\n");
}
