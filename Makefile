NAME =		asm
FLAGS =		-Wall -Wextra -Werror
SRC	=		start.c params.c aux.c ft_arg_join.c ft_hex.c \
			ft_swp_bits.c ft_write_in.c helpers.c parse.c \
			print.c utils.c ft_gnl.c
LIB	=		./libft/libft.a

SRCDIR = ./
SRCNAMES = $(shell ls $(SRCDIR) | grep -E ".+\.c")
SRC = $(addprefix $(SRCDIR), $(SRCNAMES))
INC = ./inc/
BUILDDIR = ./
BUILDOBJS = $(addprefix $(BUILDDIR), $(SRCNAMES:.c=.o))

LIBDIR = ./libft/
LIBFT = ./libft/libft.a
LIBINC = ./libft/

CC = gcc
CFLAGS =

all: $(NAME)

$(BUILDDIR)%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) -I$(LIBINC) -I$(INC) -o $@ -c $<

$(NAME): $(LIBFT) $(BUILDOBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(BUILDOBJS) $(LIBFT)

$(LIBFT):
	make -C $(LIBDIR)

clean:
	rm -f $(BUILDOBJS)
	make clean -C $(LIBDIR)

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIBDIR)

re: fclean all

.PHONY: all fclean clean re

