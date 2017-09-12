# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/25 14:30:45 by qdequele          #+#    #+#              #
#    Updated: 2017/09/12 17:38:07 by eebersol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s).so
endif

CFLAGS 	:= -fPIC -O3 -g -Wall -Werror

CC 		:= gcc

NAME 	:= libft_malloc_$(HOSTTYPE)

SRC 	:= 	main.c \
			malloc.c \
			init_struct.c

LIB 	:= libft/libft.a

OBJ 	:= $(SRC:.c=.o)

PHONY: all libft clean fclean re

all : libft $(NAME)

$(NAME):  $(OBJ)
	@make -C libft/
	@$(CC) -shared -o $(NAME) $(OBJ) $(LIB)
	@ln -s $(NAME) libft_malloc.so
	@echo "!"
	@echo "$(NAME) compiled\033[0m"

libft :
	@make -C libft/

%.o : %.c
	@$(CC) -c $(CFLAGS) -I./includes/ -I./libft/includes $<
	@printf "\033[32m."

clean :
	@make -C libft/ clean
	@/bin/rm -f $(OBJ)
	@/bin/rm -f libft_malloc.so
	@echo "\033[31m$(NAME) objects deleted\033[0m"

fclean : allclean
	@/bin/rm -f $(NAME)
	@echo "\033[31m$(NAME) deleted\033[0m"

allclean :
	@make -C libft/ fclean
	@/bin/rm -f libft_malloc.so
	@/bin/rm -f $(OBJ)
	@echo "\033[31m$(NAME) objects deleted\033[0m"

re : fclean all