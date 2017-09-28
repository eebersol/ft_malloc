/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/28 15:23:48 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <stdio.h>
# include <sys/mman.h>
# include <string.h>

# define TINY_BLOCK 90
# define SMALL_BLOCK 300
# define PAGE_SIZE sysconf(_SC_PAGESIZE)

typedef enum				e_zone_type
{
							TINY,
							SMALL,
							LARGE
}							t_zone_type;

typedef struct				s_zone	t_zone;

typedef struct				s_zone
{
	void					*addr;
	size_t					nbr_block;
	size_t					nbr_block_used;
	t_zone					*next;
	t_zone_type				type;
	int 					display;
}							t_zone;

typedef struct				s_base
{
	void					*realloc_src;
	int 					realloc_size;
	int						realloc_new_zone;
	int						realloc_flag;
	int						is_realloc;
	t_zone_type				realloc_type;
	t_zone_type				type;	
	t_zone 					*memory;
}							t_base;


int 	search_better(void *addr, t_zone *small);
void 	display_zone_with_order(t_base *base);
// malloc.c
void						*find_place(t_base *base, t_zone *zone, size_t size);
void						*malloc_memcpy(void *dst, const void *src, size_t n);
void						*malloc(size_t size);
// free.c
void						del_zone(t_zone **zone, int at, int block_size, int nbr_block);
t_zone						*browse_zone(t_zone *zone);
void						verify_zone(t_base *base);
int							check_zone(t_zone *zone, void *ptr);
void						free(void *ptr);
// realloc.c
void						*modify_base(void *ptr, size_t new_size);
void						*browse_zone_realloc(t_zone *zone, void *old_ptr, size_t new_size, int flag);
void						*find_old_alloc(t_base *base, void *ptr, size_t new_size);
void						*realloc(void *ptr, size_t size);
// show_alloc_mem.c
t_zone 						*sort_zone(t_base *base);
void 						printf_info_zone(void *ptr, int i, t_zone_type type);
void 						print_info_block(void *ptr, int i, int size);
int 						print_zone(t_zone *zone);
void 						print_info(void *ptr, int i, int jump, int size);
void						show_alloc_mem(void);
size_t 						display_block(t_zone *zone);
int							count_len_zone(t_zone *zone);
// tools.c
void						*smap(size_t len);
t_zone						*create_zone(size_t size);
int							count_len_zone(t_zone *zone);
// tools_get.c
t_zone						*get_zone(void);
t_zone_type					get_type(size_t size);
size_t						get_size_type(t_zone_type type);
size_t						get_size_zone(t_zone_type type, size_t size);
size_t						get_nbr_block(size_t size);
// init_struct.c 
void						init_base(void);
t_base						*recover_base(void);
// tools_lib.c

void	ft_lstaddend(t_zone **alst, t_zone *new);
void						ft_putnbr(int n);
void 						ft_putstr(char *str);
char						*ft_itohex(void *ptr);
t_zone *sort_list(t_zone *zoneTiny, t_zone *zoneSmall, t_zone *zoneLarge);
void						ft_lst_bubble_sort(t_zone *node);
void						ft_lst_swap(t_zone *node1, t_zone *node2);
#endif
