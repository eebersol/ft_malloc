/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/25 15:53:56 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/malloc.h"

void printf_info_zone(void *ptr, int i)
{
	ft_putstr("\n-n°");
	ft_putnbr(i);
	ft_putstr("TINY : ");
	ft_putstr(ft_itohex(ptr));
	ft_putstr("-\n\n");

}
void print_info_block(void *ptr, int i, int jump, int size)
{
	ft_putstr("TEST   [");
	ft_putnbr(i);
	ft_putstr("] 0x");
	ft_putstr(ft_itohex(ptr + sizeof(int)));
	ft_putstr("- 0x"); // pb avec le space
	ft_putstr(ft_itohex(ptr + jump + sizeof(int)));
	ft_putstr(": ");
	ft_putnbr(size);
	ft_putstr(" octets\n");
}

size_t display_block(t_zone *zone, int jump)
{
	void 				*ptr;
	int 				i;
	int 				size;
	int 				size_total;

	i 					= 0;
	size 				= 0;
	size_total 			= 0;
	ptr 				= zone->addr;
	while (i++ < zone->nbr_block)
	{
		if (*(int*)ptr != 0)
		{
			size 		= *(int*)ptr;
			printf("TRUE   [%d] %p - %p : %d octets\n",i, ptr  + sizeof(int), ptr + jump + sizeof(int), *(int*)ptr);
			print_info_block(ptr, i, jump, size);
			ptr 		+= sizeof(int);
			jump 		= jump == 0 ? size : jump;
			ptr 		+= jump;
			size_total 	+= size;
		}
		else
			ptr 		+= (sizeof(int)) + jump;
	}
	return (size_total);
}

void	print_zone(t_zone *zone, int jump)
{
	t_zone 	*tmp_zone;
	int size_total;
	int i;

	i = 0;
	tmp_zone = zone;
	size_total = 0;
	while (tmp_zone)
	{
		printf_info_zone(tmp_zone->addr, i);
		size_total += display_block(tmp_zone, jump);
		if (tmp_zone->next == NULL)
			break ;
		tmp_zone = tmp_zone->next;
		i++;
	}	
}
void show_alloc_meme()
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
	// printf("\n-----------------------------------------------------\n\n");
	// printf("Show_alloc_meme : \n\n");
	// printf("Len tiny  : [%d] \n", count_len_zone(base->tiny));
	// printf("Len small : [%d] \n", count_len_zone(base->small));
	// printf("Len large : [%d] \n", count_len_zone(base->large));
	// printf("\n%p\n", zone->addr);
	if (base)
	{
		print_zone(base->tiny, TINY_BLOCK);
		print_zone(base->small, TINY_BLOCK);
		print_zone(base->large, TINY_BLOCK);
		// while (zone)
		// {
		// 	printf_info_zone(zone->adress, i);
		// 	size_total += display_block(zone, jump);
		// 	if (zone->next == NULL)
		// 		break ;
		// 	zone = zone->next;
		// 	i++;
		// }
		// zone = base->small;
		// jump = SMALL_BLOCK;
		// i = 0;
		// while (zone)
		// {
		// 	printf_info_zone(zone->adress, i);
		// 	size_total += display_block(zone, jump);
		// 	if (zone->next == NULL)
		// 		break ;
		// 	zone = zone->next;
		// 	i++;
		// }
		// zone = base->large;
		// i= 0;
		// while (zone)
		// {
		// 	printf_info_zone(zone->adress, i);
		// 	size_total += display_block(zone, jump);
		// 	if (zone->next == NULL)
		// 		break ;
		// 	zone = zone->next;
		// 	i++;
		// }
	}
	printf("\nTotal : %lu octets\n", size_total);
	printf("\n-----------------------------------------------------\n");
}
