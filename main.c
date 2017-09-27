/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/27 12:23:16 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

// RELLOC large probleme quand la size de large depasse une page : 
// solution 1 : enmpecher le realloc
// solution 2 : fragmenter l'informartion

int main (int ac, char **av)
{
	int i;
	char *addr;

	i = 0;
	while (i < 1024)
	{
		i++;
	}
	return (0);
}