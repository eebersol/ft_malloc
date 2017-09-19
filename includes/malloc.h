/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/19 16:23:23 by eebersol         ###   ########.fr       */
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

# define LARGE_ZONE 999

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
	t_zone 	*tiny;
	t_zone 	*small;
	t_zone 	*large;
}					t_base;

typedef struct		s_global_ref
{
	t_zone_type 	type;
}					t_global_ref;

// show_alloc_meme.c
void 				show_alloc_meme(void);
size_t 				display_block(t_zone *zone, t_zone_type type);
int					ft_lstcount(t_zone *zone);

// malloc.c
void 				*malloc(size_t size);
void 				save_zone(t_base *base, t_zone *zoneList, t_global_ref *ref);

// tools.c
int					ft_lstcount(t_zone *zone);
t_zone 				*create_zone(size_t size);
size_t 				get_size_total(void);
t_zone 				*select_zone(void);
void 				*smap(size_t len);

// init_struct.c
void 				init_base(void);
void 				init_global_ref(void);
t_base				*recover_base(void);
t_global_ref		*recover_global_ref(void);

#endif
