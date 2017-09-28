/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/28 16:07:58 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"


t_zone_type		get_type(size_t size)
{
	return (size < TINY_BLOCK ? TINY : size < SMALL_BLOCK ? SMALL : LARGE);
}

size_t			get_size_type(t_zone_type type)
{
	return (type == TINY ? TINY_BLOCK : type == SMALL ? SMALL_BLOCK : 0);
}

size_t			get_size_zone(t_zone_type type, size_t size)
{
	return (type == TINY ?  (sizeof(t_zone)) + ((sizeof(int) + TINY_BLOCK) * 100) :
				type == SMALL ? (sizeof(t_zone)) + ((sizeof(int) + SMALL_BLOCK) * 100) :
					(sizeof(t_zone)) + ((sizeof(int) + size)));
}

size_t			get_nbr_block(size_t size)
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
