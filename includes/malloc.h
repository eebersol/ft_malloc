/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2016/10/18 13:38:10 by eebersol         ###   ########.fr       */
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


# define TINY_BLOCK 10
# define SMALL_BLOCK 100
# define PAGE_SIZE sysconf(_SC_PAGESIZE)

typedef enum e_zone_type
{
	TINY,
	SMALL,
	LARGE
} 			t_zone_type;

typedef struct		s_block t_block;
typedef struct		s_zone t_zone;

typedef struct		s_block
{
	int		 		size;
	int 			free;
	void			*ptr;
	t_block			*next;
}					t_block;

typedef struct		s_zone
{
	int		 		size;
	t_zone			*next;
	t_zone_type 	type;
	t_block			*blocks;
}					t_zone;

typedef struct		s_global
{
	t_zone			*zones;
	int 			nbr_page;
}					t_global;

t_global 			*global;

#endif
