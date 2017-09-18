/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/09/18 09:55:18 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

t_base		*recover_base (void)
{
	static t_base	base;

	return (&base);
}

t_global_ref		*recover_global_ref(void)
{
	static t_global_ref global_ref;

	return (&global_ref);
}

void 	init_global_ref ()
{
	t_global_ref 	*global_ref;

	global_ref = recover_global_ref();
}


void 	init_base ()
{
	t_base 	*base;

	base = recover_base();
}