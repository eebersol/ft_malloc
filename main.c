/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/25 14:53:35 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

// Test Realloc avec le falg realloc_new_zone
// gérer LARGE avec Realloc

int main (int ac, char **av)
{
	t_zone 		*zone;
	int 		i;
	char 		*str;
	char 		*str2;
	char 		*str3;
	double 		k;

	i = 0;

	init_base();
	// str = malloc(sizeof(char*) * 8);
	// str2 = malloc(sizeof(char*) * 8);
	// str3 = malloc(sizeof(char*) * 8);
	// printf("NEXT FREE STR\n");
	// free(str);
	// printf("NEXT FREE STR1\n");
	// free(str2);
	// printf("NEXT FREE STR2\n");
	// free(str3);
	// printf("SALUT\n");
	k = 7;
	i = 0;
	while (i++ < 50)
	{
			k = 10;
		if (i == 49)
		{
			printf("ici\n");
			str2 = malloc(sizeof(char*) * 10);
		}
		else
			str = malloc(sizeof(char*) * k);
	}
	// i = 0;
	// while (i++ < 900)
	// {
	// 		k = 10;
	// 	str = malloc(sizeof(char*) * k);
	// }
	// show_alloc_meme();
	// realloc(str, (sizeof(char*) * 12));
	// show_alloc_meme();
	realloc(str, (sizeof(char*) * 8));
	printf("ADDR %p\n", str);
	// free(str2);
	show_alloc_meme();
	// str = malloc(sizeof(char*) * 2);
	// str = malloc(sizeof(char*) * 4);
	// str = malloc(sizeof(char*) * 8);
	// str = malloc(sizeof(char*) * 6);
}