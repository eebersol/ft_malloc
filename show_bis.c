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


size_t	display_block_bis(t_zone *zone)
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
			size_total += *(int*)ptr;
		}
		ptr += (sizeof(int)) + get_size_type(zone->type);
		i++;
	}
	return (size_total);
}

int		print_zone_bis(t_zone *zone)
{
	t_zone	*tmp_zone;
	int		size_total;
	int		i;

	i = 0;
	tmp_zone = zone;
	size_total = 0;
	while (tmp_zone)
	{
		size_total += display_block_bis(tmp_zone);
		if (tmp_zone->next == NULL)
			break ;
		tmp_zone = tmp_zone->next;
		i++;
	}
	return (size_total);
}


size_t	show_alloc_mem_test(void)
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
		size_total += print_zone_bis(base->memory);
	}
	return (size_total);
}