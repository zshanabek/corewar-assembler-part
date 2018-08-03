/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vradchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 15:37:37 by vradchen          #+#    #+#             */
/*   Updated: 2018/08/03 15:37:39 by vradchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		write_magic(int fd)
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

void				ft_line_end(char *s, int i)
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

static void		ft_f(char *answer, int fd, char *str, int max)
{
	int				i;
	int				len;
	char			*s;
	int				x;

	i = -1;
	len = -1;
	if (str[i + 1] != '\"')
		exit(ft_printf("ERROR1\n"));
	s = ft_strdup(str + 1);
	ft_strdel(&str);
	while (len++ < max)
	{
		if (s[++i] == '\0' || s[i] == '\"')
		{
			ft_strncat(answer, s, i);
			if (s[i++] == '\"')
				return (ft_line_end(s, i));
			ft_strcat(answer, "\n");
			x = ft_gnl(fd, &s);
			if (x == 0 || x == -1)
				exit(ft_printf("No second \"\n"));
			i = -1;
		}
	}
	exit(ft_printf("Too big line\n"));
}

void			ft_read_header(header_t *h, int fd)
{
	char			*s;
	int				x;

	x = 0;
	s = NULL;
	h->magic = COREWAR_EXEC_MAGIC;
	while (ft_gnl(fd, &s))
	{
		if (!(*h->p) && ft_strncmp(s, NAME_CMD_STRING, 4) == 0 && x++ > -1)
			ft_f(h->p, fd, ft_strtrim(s + 5), PROG_NAME_LENGTH);
		else if (!(*h->c) && ft_strncmp(s, COMMENT_CMD_STRING, 8) == 0 && ++x > 0)
			ft_f(h->c, fd, ft_strtrim(s + 8), COMMENT_LENGTH);
		else if (ft_strequ(s, ""))
		{
		}
		else
		{
			ft_strdel(&s);
			exit(ft_printf("No name or header.\n"));
		}
		if (x == 2)
			return (ft_strdel(&s));
		ft_strdel(&s);
	}
	exit(ft_printf("No name or header.\n"));
}

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

void			ft_main2(t_opcode *ohead, header_t *h)
{
	int				fd2;

	ft_hex(ohead);
	fd2 = open("try.cor", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write_magic(fd2);
	write(fd2, &h->p, PROG_NAME_LENGTH + 4);
	ft_bot_size(fd2, ohead);
	write(fd2, &h->c, COMMENT_LENGTH + 4);
	if (ohead != NULL)
		ft_write_in(ohead, fd2);
	system("leaks asm");
}

int				main(int ac, char **av)
{
	int				fd;
	char			*line;
	header_t		*h;
	t_opcode		*ohead;

	ohead = NULL;
	line = NULL;
	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./asm test.s\n", 2);
		exit(1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit(ft_printf("Can't read source file %s\n", av[1]));
	h = malloc(sizeof(header_t));
	ft_read_header(h, fd);
	read_instr(fd, line, &ohead);
	if (!detect_blank_line(fd))
		show_error();
	iter_opcode(ohead, print_opcode);
	ft_main2(ohead, h);
}
