# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vradchen <vradchen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/11 21:08:02 by zshanabe          #+#    #+#              #
#    Updated: 2018/08/13 14:35:07 by vradchen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  =	asm
SRC   =	start.c params.c aux.c extra.c list.c ft_arg_join.c ft_hex.c \
		ft_write_in.c helpers.c parse.c      \
		utils.c ft_read_header.c ft_atoi_base.c ft_flag.c \
		ft_flag2.c ft_pr_param.c
OBJ   = $(SRC:.c=.o)
LIB   = libft/libft.a
FLAGS = -Wall -Wextra -Werror

all: 	lib $(NAME)

$(NAME):$(OBJ)
		@gcc  $(OBJ) $(LIB) -o $(NAME)
		@echo "\x1b[32mProject is successfully built\x1b[0m"

lib:
		@make -C libft

%.o:	%.c
		@gcc $(FLAGS) -g -o $@ -c $<

clean:	
		@rm -f $(OBJ)
		@make clean -C libft
		@echo "\x1b[33mObject files are cleaned\x1b[0m"

fclean: clean
		@make fclean -C libft
		@rm -f $(NAME)
		@echo "\x1b[33mAll is cleaned\x1b[0m"		

re:		fclean all

.PHONY: all clean fclean re

.NOTPARALLEL: all clean fclean re
