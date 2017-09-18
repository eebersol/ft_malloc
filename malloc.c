/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/18 11:29:42 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

void 	*malloc(size_t size)
{
	t_zone 			*zone;
	t_global_ref 	*global_ref;
	void 			*addr;

	size 				+= (sizeof(size));
	global_ref 			= recover_global_ref();
	global_ref->type 	= size < TINY_BLOCK ? TINY : size < SMALL_BLOCK  ? SMALL : LARGE;
	zone 				= select_zone();
	zone 				= create_zone();
	addr = "TOTO";
	return (addr);
}