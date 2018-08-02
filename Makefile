NAME =		asm
FLAGS =		-Wall -Wextra -Werror
SRC	=		start.c params.c aux.c ft_arg_join.c ft_hex.c \
			ft_swp_bits.c ft_write_in.c helpers.c parse.c \
			print.c utils.c
LIB	=		./libft/libft.a

all: 		$(NAME)

$(NAME):	$(FRC)
			@make -C libft
			@gcc $(SRC) $(LIB) -o $(NAME) $(FLAGS)
			@echo "\x1b[32mProject is successfully built!\x1b[0m"	

clean:
			@make -C libft clean

fclean:		clean
			@make -C libft fclean
			@rm -f $(NAME)

re: 		fclean all

.PHONY:all clean fclean re