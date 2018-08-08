#include "asm.h"

void			ft_bot_size(int fd2, t_opcode *ohead)
{
	t_opcode		*i;
	int				bot_size;
	unsigned int	len;

	len = 0;
	if (ohead == NULL)
	{
		write(fd2, &len, 4);
		return ;
	}
	i = ohead;
	while (i->next)
		i = i->next;
	bot_size = i->pos + i->size;
	len = ft_swp_bits(bot_size, 4);
	write(fd2, &len, 4);
}

char 			*ft_name(char *av)
{
	char 	*n;
	int 	i;

	n = ft_strdup(av);
	i = ft_strlen(n);
	while (i > -1)
	{
		if (n[i] == '.' || i == 0)
		{
			ft_strclr(n + i);
			break ;
		}
		i--;
	}
	n = ft_arg_join(n, ft_strdup(".corr"), 3);
	return (n);
}

void			ft_main2(t_opcode *ohead, header_t *h, char *av, int n)
{
	int				fd2;
	char			*name;
	int 			i;

	ft_hex(ohead, n);
	name = ft_name(av);
	fd2 = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_printf("Writing output program to %s\n", name);
	ft_strdel(&name);
	i = 0xf383ea00;
	write(fd2, &i, 4);
	write(fd2, &h->p, PROG_NAME_LENGTH + 4);
	ft_bot_size(fd2, ohead);
	write(fd2, &h->c, COMMENT_LENGTH + 4);
	if (ohead != NULL)
		ft_write_in(ohead, fd2);
}

int				main(int ac, char **av)
{
	int				n;	
	int				fd;
	char			*line;
	header_t		*h;
	t_opcode		*ohead;

	n = 0;
	ohead = NULL;
	line = NULL;
	if (ac != 2)
		exit(ft_printf("Usage: ./asm %s\n", av[1]));
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit(ft_printf("Can't read source file %s\n", av[1]));
	h = malloc(sizeof(header_t));
	ft_read_header(h, &n, fd);
	read_instr(fd, line, &n, &ohead);
	if (!detect_blank_line(fd))
		exit(ft_printf("Syntax error - unexpected end of input"
			" (Perhaps you forgot to end with a newline ?)\n"));
	//iter_opcode(ohead, print_opcode);
	ft_main2(ohead, h, av[1], n);
	// system("leaks asm");
}
