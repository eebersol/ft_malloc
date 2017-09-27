/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/27 17:17:11 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

void	ft_putnbr(int n)
{
	char c;

	if (n == -2147483648)
		ft_putstr("-2147483648");
	else
	{
		if (n < 0)
		{
			n = -n;
			c = '-';
			write(1, &c, 1);
		}
		if (n >= 10)
		{
			ft_putnbr(n / 10);
			ft_putnbr(n % 10);
		}
		else
		{
			c = '0' + n;
			write(1, &c, 1);
		}
	}
}

void 	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}


char	*ft_itohex(void *ptr)
{
	unsigned long long	address;
	char				*base;
	char				hex[50];
	char 				*str;
	int					i;

	base = "0123456789abcdef";
	address = (unsigned long long)ptr;
	i = 500;
	while (address)
	{
		hex[i] = base[address % 16];
		address = address / 16;
		i--;
	}
	str = &hex[i+1];
	return(str);
}

// t_zone *sort_list(t_zone *zoneTiny, t_zone *zoneSmall, t_zone *zoneLarge)
// {
// 	t_zone 	*bigZone;
// 	t_zone 	*tmpZone;
// 	t_zone 	**test;
// 	int 	small;

// 	tmpZone = zoneTiny;
// 	bigZone = tmpZone;
// 	test = &zoneSmall;
// 	small = 0;
// 	while (tmpZone)
// 	{
// 		if (tmpZone->next == NULL && small < 2)
// 		{
// 			small++;
// 			if (small == 1)
// 				tmpZone->next = zoneSmall;
// 			else
// 				tmpZone->next = zoneLarge;
// 		}
// 		else if (tmpZone->next == NULL)
// 		{
// 			break;
// 		}
// 		tmpZone = tmpZone->next;	
// 	}
// 	zoneSmall = *test;
// 	return (bigZone);
// }

t_zone *sort_list(t_zone *zoneTiny, t_zone *zoneSmall, t_zone *zoneLarge)
{
	t_zone 	*bigZone;
	t_zone 	*tmpZone;
	t_zone 	*test;
	int 	small;

	test = zoneSmall;
	tmpZone = zoneTiny;
	bigZone = tmpZone;
	small 	= 0;
	while (tmpZone)
	{
		if (tmpZone->next == NULL && small < 2)
		{
			small++;
			if (small == 1)
				tmpZone->next = zoneSmall;
			else
				tmpZone->next = zoneLarge;
		}
		else if (tmpZone->next == NULL)
		{
			break;
		}
		tmpZone = tmpZone->next;	
	}
	// while(test)
	// {
	// 	if (test->type != LARGE)
	// 	{
	// 		test->next = NULL;
	// 		break;
	// 	}
	// 	if (test->next == NULL)
	// 		break;
	// }
	// printf("Test : [%d] \n", count_len_zone(test));
	return (bigZone);
}




void	ft_lstaddend(t_zone **alst, t_zone *new)
{
	t_zone	*list;

	list = *alst;
	printf("Begin lastAdd : [%d] \n", count_len_zone(list));
	if (*alst == NULL && new)
		*alst = new;
	else
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
}

void	ft_lst_bubble_sort(t_zone *node)
{
	int			swapped;
	t_zone		*ptr1;
	t_zone		*lptr;

	lptr = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr1 = node;
		while (ptr1 && ptr1->next != lptr)
		{
			if (ptr1->addr > ptr1->next->addr)
			{
				ft_lst_swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

void	ft_lst_swap(t_zone *node1, t_zone *node2)
{
	void	*temp;

	printf("SWAP\n");
	temp = node1;
	node1 = node2;
	node2 = temp;
}