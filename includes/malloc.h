/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/26 20:18:22 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <stdio.h>
# include <sys/mman.h>
# include <string.h>

# define TINY_BLOCK 80
# define SMALL_BLOCK 163
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
}							t_zone;

typedef struct				s_base
{
	void					*realloc_src;
	int						realloc_new_zone;
	int						realloc_flag;
	int						is_realloc;
	t_zone_type				realloc_type;
	t_zone_type				type;	
	t_zone					*tiny;
	t_zone					*small;
	t_zone					*large;
}							t_base;

// malloc.c
void						*find_place(t_base *base, t_zone *zone, size_t size);
void						*malloc_memcpy(void *dst, const void *src, size_t n);
void						*malloc(size_t size);
// free.c
void						del_zone(t_zone **zone, int at, int block_size, int nbr_block);
t_zone						*browse_zone(t_zone *zone, int block_size);
void						verify_zone(t_base *base);
int							check_zone(t_zone *zone, void *ptr, int size_block);
void						free(void *ptr);
// realloc.c
void						*modify_base(void *ptr, size_t new_size);
void						*browse_zone_realloc(t_zone *zone, void *old_ptr, size_t new_size, int flag);
void						*find_old_alloc(t_base *base, void *ptr, size_t new_size);
void						*realloc(void *ptr, size_t size);
// show_alloc_mem.c
void 						printf_info_zone(void *ptr, int i, t_zone_type type);
void 						print_info_block(void *ptr, int i, int size);
int 						print_zone(t_zone *zone, t_zone_type type);
void 						print_info(void *ptr, int i, int jump, int size);
void						show_alloc_mem(void);
size_t 						display_block(t_zone *zone, t_zone_type type);
int							count_len_zone(t_zone *zone);
// tools.c
void						*smap(size_t len);
void						save_zone(t_base *base, t_zone *zoneList);
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
void						ft_putnbr(int n);
void 						ft_putstr(char *str);
char						*ft_itohex(void *ptr);

#endif
