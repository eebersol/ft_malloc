/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/27 15:11:08 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// RELLOC large probleme quand la size de large depasse une page : 
// solution 1 : enmpecher le realloc
// solution 2 : fragmenter l'informartion

#include "includes/malloc.h"

#define M (1024 * 1024)

void print(char *s)
{
	write(1, s, strlen(s));
}

int main()
{
	char *addr1;
	char *addr3;
	int i;

	i = 0;
	while (i++ < 300)
		addr1 = malloc(sizeof(char*) * 7);
	i = 0;
	while (i++ < 10)
		addr1 = malloc(sizeof(char*) * 10);
	i = 0;
	while (i++ < 10)
		addr1 = malloc(sizeof(char*) * 30);
	show_alloc_mem();
	return (0);
}

