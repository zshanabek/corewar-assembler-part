#include "asm.h"

static void	write_magic(int fd)
{
	long	magic;
	
	magic = COREWAR_EXEC_MAGIC;// 0xea83f3
	magic = ((magic >> 24) & 0xff) | ((magic << 8) & 0xff0000) |
		((magic >> 8) & 0xff00) | ((magic << 24) & 0xff000000);
	//magic = magic << 1;// nado swap bits
	//magic = magic >> 1;
	//len = ft_swp_bits(magic, 4);
	write(fd, &magic, 4);
}

void	ft_fill_info(char *answer, int fd, char *str, int max)
{
	int		i;
	int		len;
	char	*s;

	i = 0;
	len = 1;
	if (str[i] != '\"')
		exit(ft_printf("ERROR1\n"));
	s = ft_strdup(str + 1);
	while (len++ < max)
	{
		if (s[i] == '\0' || s[i] == '\"')
		{
			ft_strncat(answer, s, i);
			if (s[i++] == '\"')
			{
				clear_comment(s + i);
				while (s[i])
				{
					if (!ft_isws(s[i]))
						exit(ft_printf("Bad line1\n"));
					i++;
				}
				return (ft_strdel(&s));
			}
			ft_strcat(answer, "\n");
			len++;
			//ft_strdel(&s);
			ft_gnl(fd, &s);
			//get_next_line(fd, &s);
			i = -1;
		}
		i++;
	}
	exit(ft_printf("ERROR2\n"));
}

void	ft_read_header(header_t *h, int fd)
{
	char	*str;
	char	*s;

	s = NULL;
	str = NULL;
	h->magic = COREWAR_EXEC_MAGIC;
	while (ft_gnl(fd, &str))//while (get_next_line(fd, &str))
	{
		if (!(*h->prog_name) && ft_strncmp(str, NAME_CMD_STRING, 4) == 0)
		{
			s = ft_strtrim(str + 5);
			ft_fill_info(h->prog_name, fd, s, PROG_NAME_LENGTH);
			ft_strdel(&s);
		}
		else if (!(*h->comment) && ft_strncmp(str, COMMENT_CMD_STRING, 8) == 0)
		{
			s = ft_strtrim(str + 8);
			ft_fill_info(h->comment, fd, s, COMMENT_LENGTH);
			ft_strdel(&s);
		}
		else if (ft_strequ(str, ""))
		{
		}
		else if (*h->prog_name && *h->comment)
		{
			ft_strdel(&str);
			return ;
		}
		else
		{
			ft_strdel(&str);
			exit(ft_printf("No name or header.\n"));
		}
		ft_strdel(&str);
	}
	exit(ft_printf("No name or header.\n"));
}

void	ft_bot_size(int fd2, t_opcode *ohead)
{
	t_opcode		*i;
	int				bot_size;
	//char			*size;
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
	//size = ft_itoa_base(bot_size, 10);
	//while (ft_strlen(size) < 8)
	//	size = ft_arg_join("0", size, 2);//LEAK!!!!!!!!!!!!!!!!
	len = ft_swp_bits(bot_size, 4);
	write(fd2, &len, 4);
}

int main(int ac, char **av)
{
	int			fd;
	int			fd2;
	char		*line;
	header_t	*h;
	t_opcode	*ohead;

	ohead = NULL;
	line = NULL;
	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./asm test.s\n", 2);
		exit(1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Can't read source file %s\n", av[1]);
		exit(1);
	}
	h = malloc(sizeof(header_t));
	ft_read_header(h, fd);
	read_instr(fd, line, &ohead);
	if (!detect_blank_line(fd))
		show_error();
	iter_opcode(ohead, print_opcode);
	ft_hex(ohead);
	fd2 = open("try.cor", O_WRONLY | O_CREAT | O_TRUNC, 0644);	
	write_magic(fd2);
	write(fd2, &h->prog_name, PROG_NAME_LENGTH + 4);
	ft_bot_size(fd2, ohead);
	write(fd2, &h->comment, COMMENT_LENGTH + 4);
	if (ohead != NULL)
		ft_write_in(ohead, fd2);
	system("leaks asm");
}