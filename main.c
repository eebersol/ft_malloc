/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/11 15:45:02 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// void *mmap(void *addr, size_t length, int prot, int flags,
//            int fd, off_t offset);

#include <malloc.h>

int main(int ac, char **av)
{
	global = mmap(NULL, sizeof(t_global), PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0);
}