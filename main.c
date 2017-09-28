/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/28 15:24:09 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// RELLOC large probleme quand la size de large depasse une page : 
// solution 1 : enmpecher le realloc
// solution 2 : fragmenter l'informartion

#include "includes/malloc.h"


// int main()
// {
// 	char *LargeToSmall;
// 	char *LargeToTiny;
// 	char *LargeToLarge;
// 	char *addr3;
// 	int i;

// 	i = 0;
// 	// printf("TINY\n");
// 	// while (i++ < 300)
// 	// 	addr1 = malloc(sizeof(char*) * 7);
// 	// i = 0;
// 	// printf("SMALL\n");
// 	// while (i++ < 10)
// 	// 	addr1 = malloc(sizeof(char*) * 10);
// 	// i = 0;
// 	printf("LARGE\n");
// 	while (i++ < 10)
// 	{
// 		if (i == 3)
// 			LargeToSmall = malloc(sizeof(char*) * 3000);
// 		else if (i == 4)
// 			LargeToTiny =  malloc(sizeof(char*) * 4000);
// 		else if (i == 5)
// 			LargeToLarge = malloc(sizeof(char*) * 5000);
// 		else
// 			addr3 = malloc(sizeof(char*) * 300);
// 	}
// 	realloc(LargeToSmall, sizeof(char*) * 17);
// 	realloc(LargeToTiny, sizeof(char*) * 7);
// 	realloc(LargeToLarge, sizeof(char*) * 1700);
// 	show_alloc_mem();
// 	return (0);
// }

int    main(void)
{
    int        err;
    char    *str;
    int        i;
    
    err = 0;
    i = 290;
    while (i < 310)
    {
        printf("-------NUMBER : %d", i);
        str = (char*)malloc(i);
        str[0] = 42;
        show_alloc_mem();
        free(str);
        show_alloc_mem();
        str = (char*)malloc(i);
        str[0] = 42;
        show_alloc_mem();
        i++;
    }
    // show_alloc_mem();
    printf("\t 1) ok\n");
    return err;
}

