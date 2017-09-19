/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/19 16:26:01 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"


int main (int ac, char **av)
{
	t_zone 		*zone;
	int 		i;
	char 		*str;
	double 		k;

	i = 0;

	init_base();
	init_global_ref();


	k = 8.9;
	while (i++ < 900)
	{
		if (i > 200)
			k = 6;
		str = malloc(sizeof(char*) * k);
	}
	i = 0;
	while (i++ < 900)
	{
			k = 10;
		str = malloc(sizeof(char*) * k);
	}
	i = 0;
	while (i++ < 900)
	{
			k = 40;
		str = malloc(sizeof(char*) * k);
	}
	// str = malloc(sizeof(char*) * 2);
	// str = malloc(sizeof(char*) * 4);
	// str = malloc(sizeof(char*) * 8);
	// str = malloc(sizeof(char*) * 6);
	show_alloc_meme();
}