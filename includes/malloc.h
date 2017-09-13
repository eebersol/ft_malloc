/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/13 15:20:25 by eebersol         ###   ########.fr       */
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

# define PAGE_SIZE getpagesize()

typedef enum e_zone_type
{
	TINY,
	SMALL,
	LARGE
} 			t_zone_type;

typedef struct		s_block t_block;
typedef struct		s_zone 	t_zone;

typedef struct		s_block
{
	int		 		size;
	int 			free;
	void			*addr;
	t_block			*next;
}					t_block;

typedef struct		s_zone
{
	void			*addr;
	t_block			*block;
	t_zone			*next;
	t_zone_type 	type;
}					t_zone;

// INIT STRUCT
t_zone		*recover_zone(void);
void		init_zone(void);
void 		show_alloc_meme (void);
size_t 		display_block (t_zone *zone);
///////////////

void 		*malloc(size_t size);

// TOOLS
void 		*smap(size_t len);
t_block 	*create_block(size_t len);
t_zone 		*create_zone();
///////////////

#endif
