/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/21 15:37:49 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/mman.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>


# define TINY_ZONE 8016
# define TINY_BLOCK 80

# define SMALL_ZONE 16384
# define SMALL_BLOCK 163

# define PAGE_SIZE sysconf(_SC_PAGESIZE)

typedef enum e_zone_type
{
	TINY,
	SMALL,
	LARGE
} 			t_zone_type;

typedef struct		s_zone 	t_zone;



typedef struct		s_zone
{
	int 			test;
	void			*addr;
	t_zone			*next;
	t_zone_type 	type;
	size_t 			nbrBlock;
	size_t 			nbrBlockUsed;
}					t_zone;

typedef struct 		s_base
{
	void 			*last_realloc;
	void			*last_realloc_content;
	int				realloc_new_zone;
	int 			realloc_flag;
	void 			*realloc_content;
	void 			*realloc_src;
	size_t 			realloc_size;
	int 			is_realloc;
	t_zone_type 	realloc_type;
	t_zone_type 	type;	
	t_zone 			*tiny;
	t_zone 			*small;
	t_zone 			*large;
}					t_base;

// malloc.c
void				*malloc_memcpy(void *dst, const void *src, size_t n);
void 				*find_place(t_base *base, t_zone *zone, size_t size);
void 				*malloc(size_t size);

// free.c
void				del_zone(t_zone **zone, int at, int block_size, int nbr_block);
t_zone				*browse_zone(t_zone *zone, int block_size);
void 				verify_zone(t_base *base);
int 				check_zone(t_zone *zone, void *ptr, int size_block);
void				free(void *ptr);

// realloc.c
void 				*modify_base(void *ptr, size_t new_size);
void				*browse_zone_realloc(t_zone *zone, void *old_ptr, size_t new_size, int flag);
void 				*find_old_alloc(t_base *base, void *ptr, size_t new_size);
void 				*realloc(void *ptr, size_t size);
// show_alloc_meme.c
void 				show_alloc_meme(void);
size_t 				display_block(t_zone *zone, int jump);
int					ft_lstcount(t_zone *zone);

// tools.c
t_zone 				*get_zone(void);
void 				save_zone(t_base *base, t_zone *zoneList);
int					ft_lstcount(t_zone *zone);
t_zone 				*create_zone(size_t size);
void 				*smap(size_t len);

// tools_get.c
t_zone_type 		get_type(size_t size);
size_t 				get_size_type(t_zone_type type);
size_t 				get_size_zone(t_zone_type type, size_t size);
size_t 				get_nbr_block(size_t size);

// init_struct.c
void 				init_base(void);
t_base				*recover_base(void);

#endif
