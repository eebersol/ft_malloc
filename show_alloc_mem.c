/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/28 16:14:22 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

void	printf_info_zone(void *ptr, int i, t_zone_type type)
{
	if (type == TINY)
		ft_putstr("TINY : ");
	else if (type == SMALL)
		ft_putstr("SMALL : ");
	else
		ft_putstr("LARGE : ");
	ft_putstr("0x");
	ft_putstr(ft_itohex(ptr));
	ft_putstr("\n");
}

void	print_info_block(void *ptr, int i, int size)
{
	ft_putstr("0x");
	ft_putstr(ft_itohex(ptr + sizeof(int)));
	ft_putstr("- 0x");
	ft_putstr(ft_itohex(ptr + size + sizeof(int)));
	ft_putstr(": ");
	ft_putnbr(size);
	if (size < 1)
		ft_putstr(" octet\n");
	else
		ft_putstr(" octets\n");
}

size_t	display_block(t_zone *zone)
{
	void	*ptr;
	int		size_total;
	int		i;

	size_total = 0;
	ptr = zone->addr;
	i = 0;
	while (i < (int)zone->nbr_block_used)
	{
		if (*(int*)ptr != 0)
		{
			print_info_block(ptr, i, *(int*)ptr);
			size_total += *(int*)ptr;
		}
		ptr += (sizeof(int)) + get_size_type(zone->type);
		i++;
	}
	return (size_total);
}

int		print_zone(t_zone *zone)
{
	t_zone	*tmp_zone;
	int		size_total;
	int		i;

	i = 0;
	tmp_zone = zone;
	size_total = 0;
	while (tmp_zone)
	{
		printf_info_zone(tmp_zone->addr, i, tmp_zone->type);
		size_total += display_block(tmp_zone);
		if (tmp_zone->next == NULL)
			break ;
		tmp_zone = tmp_zone->next;
		i++;
	}
	return (size_total);
}

void	show_alloc_mem(void)
{
	t_base	*base;
	t_zone	*zone;
	size_t	size_total;

	zone = NULL;
	base = recover_base();
	size_total = 0;
	if (base->memory)
	{
		ft_lst_bubble_sort(base->memory);
		size_total += print_zone(base->memory);
	}
	ft_putstr("Total : ");
	ft_putnbr((int)size_total);
	if (size_total < 1)
		ft_putstr(" octet\n");
	else
		ft_putstr(" octets\n");
}
