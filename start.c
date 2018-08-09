/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vradchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 11:16:46 by vradchen          #+#    #+#             */
/*   Updated: 2018/08/08 11:16:47 by vradchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdio.h>

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

char			*ft_name(char *av)
{
	char	*n;
	int		i;

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
	int				i;

	ft_h(ohead, n);
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

int 			ft_check_ac(int ac, char **av, char **name)
{
	if (ac == 3)
	{
		if (!(ft_strequ(av[1], "-a") || ft_strequ(av[2], "-a")))
			exit(ft_printf("Usage: ./asm %s\n", av[2]));
		if (ft_strequ(av[1], "-a"))
		{
			*name = av[2];
			return (2);
		}
		*name = av[1];
		return (1);
	}
	else if (ac != 2)
		exit(ft_printf("Usage: ./asm %s\n", av[1]));
	*name = av[1];
	return (0);
	//return (av[1]);
}

int 			ft_ohead_size(t_opcode *ohead)
{
	int			size;
	t_opcode	*h;

	h = ohead;
	size = 0;
	while (h->next)
		h = h->next;
	size = h->size + h->pos;
	return (size);
}

void			ft_pr_param1(t_param *p)
{
	if (p->type == 1)
		ft_printf("r%-18i",p->ival);
	else if (p->type == 2)
	{
		if (p->sval == NULL)
			ft_printf("%%%-18i",p->ival);
		else
			ft_printf("%%:%-17s",p->sval);
	}
	else if (p->type == 3)
	{
		if (p->sval == NULL)
			ft_printf("%-19i",p->ival);
		else
			ft_printf(":%-18s",p->sval);
	}
}

void			ft_pr_param2(t_param *p)
{

}

void			ft_pr_param3(t_param *p)
{
	if (p->type == 1)
		ft_printf2("%-19i",p->ival);
	else if (p->type == 2)
	{
		if (p->sval == NULL)
			ft_printf2("%-19i",p->ival);
		else
			ft_printf2("%-19i", search_struct(p->sval)->opcode);
	}
	else if (p->type == 3)
	{
		if (p->sval == NULL)
			ft_printf2("%-19i",p->ival);
		else
			ft_printf2("%-19i",search_struct(p->sval)->opcode);
	}
	if (p->next == NULL)
		ft_printf2("\n");
}
void			ft_print_flag(t_opcode *in)
{
	t_label	*l;
	t_param	*p;

	l = in->label;
	while (l)
	{
		//ft_printf("%-11i:%6s:\n", in->pos, l->name);
		l = l->next;
	}
	ft_printf("%-5i(%-3i) :        %-10s", in->pos, in->size, op_tab[in->opcode - 1].name);
	p = in->param;
	while (p)
	{
		ft_pr_param1(p);
		p = p->next;
	}
	ft_printf2("\n                    %-4lld", in->opcode);
	if (in->codage == 1)
		ft_printf2("%-6lld", ft_bin_to(ft_write_in2(in)));
	else
		ft_printf2("%-6");
	p = in->param;
	while (p)
	{
		ft_pr_param2(p);
		p = p->next;
	}
	ft_printf2("\n                    %-4lld", in->opcode);
	if (in->codage == 1)
		ft_printf2("%-6lld", ft_bin_to(ft_write_in2(in)));
	else
		ft_printf2("%-6");
	p = in->param;
	while (p)
	{
		ft_pr_param3(p);
		p = p->next;
	}
}

int				main(int ac, char **av)
{
	int				n;
	int				fd;
	char			*line;
	header_t		*h;
	t_opcode		*ohead;
	int 			fd2;
	char 			*name;
	int 			i;
	int 			flag;

	flag = 0;
	n = 0;
	ohead = NULL;
	line = NULL;
	flag = ft_check_ac(ac, av, &name);
	fd = open(name, O_RDONLY);
	if (fd == -1)
		exit(ft_printf("Can't read source file %s\n", name));
	h = malloc(sizeof(header_t));
	ft_read_header(h, &n, fd);
	read_instr(fd, line, &n, &ohead);
	if (!detect_blank_line(fd))
		exit(ft_printf("Syntax error - unexpected end of input"
			" (Perhaps you forgot to end with a newline ?)\n"));
//	iter_opcode(ohead, print_opcode);
	ft_h(ohead, n);
	name = ft_name(name);
	fd2 = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (flag > 0)
	{
		//ft_printf(("Dumping annotated program on standard output\nProgram size "
		//": %i bytes\nName : \"%s\"\nComment : \"%s\"\n\n"),ft_ohead_size(ohead),
		//h->p, h->c);
		iter_opcode(ohead, ft_print_flag);
	}
	else
		ft_printf("Writing output program to %s\n", name);
	ft_strdel(&name);
	i = 0xf383ea00;
	write(fd2, &i, 4);
	write(fd2, &h->p, PROG_NAME_LENGTH + 4);
	ft_bot_size(fd2, ohead);
	write(fd2, &h->c, COMMENT_LENGTH + 4);
	if (ohead != NULL)
		ft_write_in(ohead, fd2);
	//ft_main2(ohead, h, av[1], n);
	// system("leaks asm");
}
