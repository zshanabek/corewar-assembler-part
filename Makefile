NAME  =	asm
SRC   =	start.c params.c aux.c ft_arg_join.c ft_hex.c \
		ft_swp_bits.c ft_write_in.c helpers.c parse.c \
		print.c utils.c
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
		@gcc $(FLAGS) -o $@ -c $<

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