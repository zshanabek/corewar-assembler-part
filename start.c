/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zshanabe <zshanabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 11:16:46 by vradchen          #+#    #+#             */
/*   Updated: 2018/09/12 12:57:31 by zshanabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			ft_main2(t_opcode *ohead, t_header *h, char **name)
{
	int				fd;
	int				i;

	fd = open(*name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_strdel(name);
	i = 0xf383ea00;
	write(fd, &i, 4);
	write(fd, &h->p, PROG_NAME_LENGTH + 4);
	ft_bot_size(fd, ohead);
	write(fd, &h->c, COMMENT_LENGTH + 4);
	if (ohead != NULL)
		ft_write_in(ohead, fd);
}

void			ft_main3(t_header *h, int n, char *name, t_opcode **ohead)
{
	int		fd;

	fd = open(name, O_RDONLY);
	ft_read_header(h, &n, fd);
	read_instr(fd, &n, ohead);
	if (!detect_blank_line(fd))
		exit(ft_printf(2, "Syntax error - unexpected end of input"
			" (Perhaps you forgot to end with a newline?)\n"));
	ft_h(*ohead, n);
}

void			ft_main4(t_opcode *ohead, t_header *h)
{
	ft_printf(1, "Dumping annotated program on standard output\nProgram size "
		": %i bytes\nName : \"%s\"\nComment : \"%s\"\n", ft_ohead_size(ohead),
		h->p, h->c);
	iter_opcode2(ohead, ft_print_flag);
	exit(1);
}

int				main(int ac, char **av)
{
	t_header		*h;
	t_opcode		*ohead;
	char			*name;
	int				n;
	int				flag;

	n = 0;
	ohead = NULL;
	flag = ft_check_ac(ac, av, &name);
	if (open(name, O_RDONLY) == -1)
		exit(ft_printf(2, "Can't read source file %s\n", name));
	h = malloc(sizeof(t_header));
	ft_main3(h, n, name, &ohead);
	name = ft_name(name);
	if (flag > 0)
		ft_main4(ohead, h);
	else
		ft_printf(1, "Writing output program to %s\n", name);
	ft_main2(ohead, h, &name);
}
