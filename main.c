/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/28 16:15:10 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// RELLOC large probleme quand la size de large depasse une page : 
// solution 1 : enmpecher le realloc
// solution 2 : fragmenter l'informartion

#include "includes/malloc.h"

#define M1 (1024 * 1024)

void		print(char *s)
{
	write(1, s, strlen(s));
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int		test_6(void)
{
	malloc(1024);
	malloc(1024 * 32);
	malloc(1024 * 1024);
	malloc(1024 * 1024 * 16);
	malloc(1024 * 1024 * 128);
	ft_putstr("\n---------show_alloc_mem()------------\n");
	show_alloc_mem();
	return (0);
}
int			test_5(void)
{
	char	*addr;
	char	*test;

	addr = malloc(16);
	free(NULL);
	free((void *)addr + 5);
	test = realloc((void *)addr + 5, 10);
	if (test == NULL)
		print("Bonjours\n");
	return (0);
}

int			test_4_1(void)
{
	char	*addr1;
	char	*addr2;
	char	*addr3;

	addr1 = (char *)malloc(16 * M1);
	strcpy(addr1, "Bonjours\n");
	print(addr1);
	addr2 = (char *)malloc(16 * M1);
	addr3 = (char *)realloc(addr1, 128 * M1);
	addr3[127 * M1] = 42;
	print(addr3);
	return (0);
}

int			test_4(void)
{
	char	*addr1;
	char	*addr3;

	addr1 = (char *)malloc(16 * M1);
	strcpy(addr1, "Bonjours\n");
	print(addr1);
	addr3 = (char *)realloc(addr1, 128 * M1);
	addr3[127 * M1] = 42;
	print(addr3);
	return (0);
}

int			test_3(void)
{
	char	*addr1;
	char	*addr3;

	addr1 = (char *)malloc(16 * M1);
	strcpy(addr1, "Bonjours\n");
	print(addr1);
	addr3 = (char *)realloc(addr1, 128 * M1);
	addr3[127 * M1] = 42;
	print(addr3);
	return (0);
}

int		test_2(void)
{
	int		i;
	char	*addr;

	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
		addr[0] = 42;
		i++;
	}
	return (0);
}

int			test_1(void)
{
	int		i;
	char	*addr;

	i = 0;
	while (i < 1024)
	{
		i++;
	}
	return (0);
}

int 	test_realloc()
{
	char 	*large_to_tiny;
	char 	*large_to_small;
	char 	*large_to_large;

	char 	*tiny_to_tiny;
	char 	*tiny_to_small;
	char 	*tiny_to_large;

	char 	*small_to_tiny;
	char 	*small_to_small;
	char 	*small_to_large;

	large_to_tiny  = (char*)malloc(sizeof(char*) * 6);
	large_to_small = (char*)malloc(sizeof(char*) * 1500);
	large_to_large = (char*)malloc(sizeof(char*) * 1500);

	tiny_to_tiny = (char*)malloc(sizeof(char*) * 3);
	tiny_to_small = (char*)malloc(sizeof(char*) * 3);
	tiny_to_large = (char*)malloc(sizeof(char*) * 3);

	small_to_tiny = (char*)malloc(sizeof(char*) * 15);
	small_to_small = (char*)malloc(sizeof(char*) * 15);
	small_to_large = (char*)malloc(sizeof(char*) * 15);

	large_to_tiny = realloc(large_to_tiny, (sizeof(char*) * 6));
	large_to_small = realloc(large_to_small, (sizeof(char*) * 30));
	large_to_large = realloc(large_to_large, (sizeof(char*) * 3000));

	tiny_to_tiny = realloc(tiny_to_tiny, (sizeof(char*) *  6));
	tiny_to_small = realloc(tiny_to_small, (sizeof(char*) * 30));
	tiny_to_large = realloc(tiny_to_large, (sizeof(char*) * 3000));

	small_to_tiny = realloc(small_to_tiny, (sizeof(char*) * 6));
	small_to_small = realloc(small_to_small, (sizeof(char*) * 30));
	small_to_large = realloc(small_to_large, (sizeof(char*) * 3000));	

	free(large_to_tiny);
	free(large_to_small);
	free(large_to_large);
	free(small_to_tiny);
	free(small_to_small);
	free(small_to_large);
	free(tiny_to_tiny);
	free(tiny_to_small);
	free(tiny_to_large);

	printf("Test 3 - realloc OK.\n");

	return (0);
}


int 	test_free(void)
{
	char 	*strTiny;
	char 	*strSmall;
	char 	*strLarge;
	int 	i;

	i 		 = 0;
	strTiny  = (char*)malloc(sizeof(char*) * 8);
	strSmall = (char*)malloc(sizeof(char*) * 13);
	strLarge = (char*)malloc(sizeof(char*) * 130);;
	free(strTiny);
	free(strSmall);
	free(strLarge);
	printf("Test 2 - free OK.\n");
	return (0);

}

int 	test_malloc(void)
{
	char 	*str;
	int 	i;
	int 	size;

	i 		= 0;
	size 	= 8;
	while (i++ < 300)
	{
		size = i < 100 ? 7 : i < 200 ? 13 : 310;
		str = (char*)malloc(15);
	}
	if (str != NULL)
		printf("Test 1 - malloc OK.\n");
	else
		printf("Test 1 - fail.\n");
	return (0);
}

int main(void)
{
	char 	*str;
	int 	i;

	i = 0;
	// test_malloc();
	// test_free();
	// test_realloc();
	// printf("Test github : \n");
	// test_1();
	// test_2();
	// test_3();
	// test_4();
	// test_4_1();
	// test_5();
	// test_6();
	printf("All OK \n");

	return (0);
}