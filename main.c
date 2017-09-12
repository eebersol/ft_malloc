/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/12 17:38:09 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// void *mmap(void *addr, size_t length, int prot, int flags,
//            int fd, off_t offset);

#include "includes/malloc.h"

void 	*ft_malloc (size_t size)
{
	t_zone *zone;
	int *allocation;

	zone = recover_zone();
	printf("COUCOU\n");	
	size += sizeof(size);
	allocation = mmap(NULL, size, PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0);

	*allocation = size;
	// printf("%zu\n", size);
	// printf("%p\n", (void*)(&allocation));
	// printf("%ld\n", PAGE_SIZE);
	return (void*)(&allocation[0]);
}

int main (int ac, char **av)
{
	char *str;
	int i;

	init_zone();
	// global = mmap(NULL, sizeof(t_global), PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0);
	str = ft_malloc(sizeof(char*) * 50000);
	i = 0;
	// while (i < 50000)
	// {
	// 	str[i] = 'a';
	// 	printf(" LA %c %d\n",str[i], i);
	// 	i++;
	// }

}