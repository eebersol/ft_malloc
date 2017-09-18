/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/18 09:31:54 by eebersol         ###   ########.fr       */
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
	void			*addr;
	t_zone			*next;
	t_zone_type 	type;
	size_t 			nbrBlock;
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


// t_ref 				*g_ref;
// INIT STRUCT
void 	init_global_ref ();
t_global_ref		*recover_global_ref(void);
t_base		*recover_base(void);
void		init_base(void);
void 		show_alloc_meme (void);
size_t 		display_block (t_zone *zone);
///////////////

void 		*malloc(size_t size);

// TOOLS
void 			*smap(size_t len);
t_zone 			*create_zone();
t_zone 			*select_zone();
int				ft_lstcountzone(t_zone *lst);
///////////////


#endif
