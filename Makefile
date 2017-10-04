# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/25 14:30:45 by qdequele          #+#    #+#              #
#    Updated: 2017/09/28 16:13:10 by eebersol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

CFLAGS 	:= -fPIC -O3 -g -Wall -Werror

CC 		:= gcc

NAME 	:= libft_malloc_$(HOSTTYPE).so

SRC 	:=  malloc.c \
			init_struct.c \
			tools.c \
			tools_get.c \
			tools_lib.c \
			show_alloc_mem.c \
			free.c \
			realloc.c \
			show_bis.c 

OBJ 	:= $(SRC:.c=.o)

PHONY: all  clean fclean re

all : $(NAME) 

$(NAME):  $(OBJ)
	@$(CC) -shared -o $(NAME) $(OBJ)
	@ln -s $(NAME) libft_malloc.so
	@echo "$(NAME) compiled\033[0m"

%.o : %.c
	@$(CC) -c $(CFLAGS) $< -I./includes/
	@echo  "\033[32m."

clean :
	@/bin/rm -f $(OBJ)
	@/bin/rm -f libft_malloc.so
	@echo "\033[31m$(NAME) objects deleted\033[0m"

fclean : allclean
	@/bin/rm -f $(NAME)
	@echo "\033[31m$(NAME) deleted\033[0m"

allclean :
	@/bin/rm -f libft_malloc.so
	@/bin/rm -f $(OBJ)
	@echo "\033[31m$(NAME) objects deleted\033[0m"

test : re
	@gcc main.c $(NAME)
	@./a.out

re : fclean all 
