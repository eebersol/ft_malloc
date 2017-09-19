# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/25 14:30:45 by qdequele          #+#    #+#              #
#    Updated: 2017/09/19 15:50:19 by eebersol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s).so
endif

CFLAGS 	:= -fPIC -O3 -g -Wall -Werror

CC 		:= gcc

NAME 	:= libft_malloc_$(HOSTTYPE)

SRC 	:=  malloc.c \
			init_struct.c \
			tools.c \
			show_alloc_mem.c


OBJ 	:= $(SRC:.c=.o)

PHONY: all  clean fclean re

all : $(NAME) 

$(NAME):  $(OBJ)
	@$(CC) -shared -o $(NAME) $(OBJ)
	@ln -s $(NAME) libft_malloc.so
	@echo "$(NAME) compiled\033[0m"
	@gcc main.c $(NAME)
	@./a.out

%.o : %.c
	@$(CC) -c $(CFLAGS) $< -I./includes/
	@printf "\033[32m."

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

re : fclean all 