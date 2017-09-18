/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/18 11:29:40 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

int main (int ac, char **av)
{
	t_zone 		*zone;
	int 		i;
	char 		*str;

	i = 0;
	init_base();
	init_global_ref();
	str = malloc(sizeof(char*) * 2);
	// str = malloc(sizeof(char*) * 300);
	// str = malloc(sizeof(char*) * 400);
	// str = malloc(sizeof(char*) * 5000);
	// str = malloc(sizeof(char*) * 6);
}