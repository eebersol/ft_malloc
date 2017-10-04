/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/10/04 13:23:18 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

#define M1 (1024 * 1024)

int	g_ttx;

typedef void		(*t_func)(void);

typedef struct		s_functions
{
	char			*num;
	int				size;
	t_func			f;
}					t_functions;


void	test_malloc_1(void)
{
	char	*str;
	int		i;

	str = malloc(42);
	str = malloc(420);
	str = malloc(4200);
}

void	test_malloc_2(void)
{
	char	*str;
	int		i;

	i = 290;
	while (i < 310)
	{
		str = malloc(i);
		str[0] = 42;
		i += 1;
	}
}

void	test_free_1(void)
{
	char	*str;
	int		i;

	i = 290;
	while (i < 310)
	{
		str = malloc(i);
		str[0] = 42;
		free(str);
		str = malloc(i);
		str[0] = 42;
		i++;
	}
}

void	test_realloc_1(void)
{
	char	*addr;
	char	*test;

	addr = malloc(90);
	test = realloc(addr, 10);
}

void	test_realloc_2(void)
{
	char	*str;

	str = malloc(TINY - 10);
	str = realloc(str, TINY + 10);
	str = realloc(str, SMALL + 1000);
	str = realloc(str, TINY - 10);
	str = realloc(str, SMALL - 10);
}

void	test_realloc_3(void)
{
	char	*str;
	int		i;

	str = malloc(10);
	i = 0;
	while (i < 10)
	{
		str[i] = i + 'a';
		i++;
	}
	str[i] = '\0';
	str = realloc(str, 15);
}

void	test_realloc_4(void)
{
	char	*str;
	int		i;

	str = malloc(1000);
	i = 0;
	while (i < 1000)
	{
		str[i] = i + 'a';
		i++;
	}
	str[i] = '\0';
	str = realloc(str, 5);
}

int	test(char *num, t_func f, int size)
{
	int		ttx;
	f();
	ttx = show_alloc_mem_test();
	if (ttx - g_ttx != size)
	{
		
		ft_putstr(num);
		ft_putstr(") Error | ");
		ft_putnbr(ttx - g_ttx);
		ft_putstr(" != ");
		ft_putnbr(size);
		ft_putstr("\n");
		g_ttx = ttx;
		return (1);
	}
	else
	{
		g_ttx = ttx;
		ft_putstr(num);
		ft_putstr(") OK\n");
		return (0);
	}
}



int	main(void)
{
	int err;
	int i;
	t_functions	f[] = {
		{"1.1", 4662, test_malloc_1},
		{"1.2", 5990, test_malloc_2},
		{"2.1", 5990, test_free_1},
		{"3.1", 10, test_realloc_1},
		{"3.2", SMALL - 10, test_realloc_2},
		{"3.3", 15, test_realloc_3},
		{"3.4", 5, test_realloc_4},
		{NULL, 0,  NULL}
	};
	i = 0;
	while (f[i].num)
	{
		err += test(f[i].num, f[i].f, f[i].size);
		i++;
	}
	
	return err;
}