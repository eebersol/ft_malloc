/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/12 17:38:07 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void 	*malloc(size_t size)
{
	int *allocation;

	printf("COUCOU\n");	
	size += sizeof(size);
	allocation = mmap(NULL, size, PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0);

	*allocation = size;
	return (void*)(&allocation[0]);
}