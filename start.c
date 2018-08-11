/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zshanabe <zshanabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 11:16:46 by vradchen          #+#    #+#             */
/*   Updated: 2018/08/11 13:18:14 by zshanabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char *temp;

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
	temp = *name;
	if (temp[ft_strlen(temp) - 1] != 's')
		exit(ft_printf("Wrong file without .s extension\n"));
	return (0);
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
		ft_printf("r%-17i",p->ival);
	else if (p->type == 2)
	{
		if (p->sval == NULL)
			ft_printf("%%%-17i", p->ival);
		else
			ft_printf("%%:%-16s", p->sval);
	}
	else if (p->type == 3)
	{
		if (p->sval == NULL)
			ft_printf("%-18i",p->ival);
		else
			ft_printf(":%-17s",p->sval);
	}
}

char 			*ft_console(int v)//t_param *p)
{
	char 	*ret;
	int 	value;
	int 	i;

	value = v;//-p->ival;
	ret = ft_itoa_base(value, 2);
//	if (p->size == 4)
//	{
//		while (ft_strlen(ret) < 32)
//			ret = ft_arg_join(ft_strdup("0"), ret, 3);
//	}
//	else
		while (ft_strlen(ret) < 16)
			ret = ft_arg_join(ft_strdup("0"), ret, 3);
	i = ft_strlen(ret) - 1;
	while (i > -1)
	{
		if (ret[i] == '0')
			ret[i] = '1';
		else
			ret[i] = '0';
		i--;
	}
	i = ft_strlen(ret) - 1;
	while (i > -1)
	{
		if (ret[i] == '0')
		{
			ret[i] = '1';
			break ;
		}
		if (i == 0)
		{
			ret = ft_arg_join("1", ret, 3);
			break ;
		}
		i--;
	}
	return (ret);
}

int			ft_print_l2(t_opcode *instr, t_opcode *in, t_param *p)
{
	t_opcode	*i;
	t_label		*l;

	i = instr;
	while (i)
	{
		l = i->label;
		while (l)
		{
			if (ft_strequ(l->name, p->sval))
			{
				if (i->pos - in->pos > 0)
					ft_console(i->pos - in->pos);
				return (i->pos - in->pos);
			}
			l = l->next;
		}
		i = i->next;
	}
	return (0);
}

void			ft_pr_param2(t_param *p, t_opcode *in, t_opcode *ohead)
{
	char 	*hex;
	char 	*two;
	int 	i;
	int 	value;
	char 	*ret;
	two = ft_strnew(2);
	i = 0;
	if (p->type == 1)
		ft_printf2("%-18i",p->ival);
	else
	{
		if (p->sval == NULL)
		{
			if (p->ival < 0)
			{
//				value = -p->ival;
//				ret = ft_itoa_base(value, 2);
//				if (p->size == 4)
//				{
//					while (ft_strlen(ret) < 32)
//						ret = ft_arg_join(ft_strdup("0"), ret, 3);
//				}
//				else
//					while (ft_strlen(ret) < 16)
//						ret = ft_arg_join(ft_strdup("0"), ret, 3);
//				i = ft_strlen(ret) - 1;
//				while (i > -1)
//				{
//					if (ret[i] == '0')
//						ret[i] = '1';
//					else
//						ret[i] = '0';
//					i--;
//				}
//				i = ft_strlen(ret) - 1;
//				while (i > -1)
//				{
//					if (ret[i] == '0')
//					{
//						ret[i] = '1';
//						break ;
//					}
//					if (i == 0)
//					{
//						ret = ft_arg_join("1", ret, 3);
//						break ;
//					}
//					i--;
//				}
				ret = ft_console(p->ival);
				hex = ft_itoa_base(ft_atoi_base(ret, 2), 16);
				ft_strdel(&ret);
			}
			else
				hex = ft_itoa_base(p->ival, 16);
		}
		else
			hex = ft_itoa_base(ft_print_l2(ohead, in, p), 16);
		while (ft_strlen(hex) < 8)
			hex = ft_arg_join(ft_strdup("0"), hex, 3);
		if (p->size == 4)
		{
			while (i != 8)
			{
				two[0] = hex[i];
				two[1] = hex[i + 1];
				ft_printf2("%-4i", ft_atoi_base(two, 16));
				i += 2;
			}
			ft_printf2("%2s", " ");
		}
		else if (p->size == 2)
		{
			i = 4;
			while (i != 8)
			{
				two[0] = hex[i];
				two[1] = hex[i + 1];
				ft_printf2("%-4i", ft_atoi_base(two, 16));
				i += 2;
			}
			ft_printf2("%10s", " ");
		}
	}
//	else if (p->type == 3)
//	{
//		if (p->sval == NULL)
//		{
//			ft_printf2("%-19i",p->ival);
//		}
//		else
//		{
//			ft_printf2("%-19i",p->sval);
//		}
//	}
}

void			ft_pr_param3(t_param *p, t_opcode *in, t_opcode *ohead)
{
	if (p->type == 1)
		ft_printf2("%-18i",p->ival);
	else //if (p->type == 2)
	{
		if (p->sval == NULL)
			ft_printf2("%-18i",p->ival);
		else
			ft_printf2("%-18i", ft_print_l2(ohead, in, p));
	}
//	else if (p->type == 3)
//	{
//		if (p->sval == NULL)
//			ft_printf2("%-19i",p->ival);
//		else
//			ft_printf2("%-19i", ft_print_l2(ohead, in, p));
//	}
	//if (p->next == NULL)
	//	ft_printf2("\n");
}

void			ft_print_flag(t_opcode *in, t_opcode *ohead)
{
	t_label	*l;
	t_param	*p;

	l = in->label;
	while (l)
	{
		ft_printf("\n%-11i:    %s:", in->pos, l->name);
		l = l->next;
	}
	ft_printf("\n%-5i(%-3i) :        %-10s", in->pos, in->size,
		op_tab[in->opcode - 1].name);
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
		ft_printf2("%6s", " ");
	p = in->param;
	while (p)
	{
		ft_pr_param2(p, in, ohead);
		p = p->next;
	}
	ft_printf2("\n                    %-4lld", in->opcode);
	if (in->codage == 1)
		ft_printf2("%-6lld", ft_bin_to(ft_write_in2(in)));
	else
		ft_printf2("%6s", " ");
	p = in->param;
	while (p)
	{
		ft_pr_param3(p, in, ohead);
		p = p->next;
	}
	ft_printf2("\n");
	if (in->next == NULL)
		ft_printf2("\n");
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
		ft_printf(("Dumping annotated program on standard output\nProgram size "
		": %i bytes\nName : \"%s\"\nComment : \"%s\"\n"),ft_ohead_size(ohead),
		h->p, h->c);
		iter_opcode2(ohead, ft_print_flag);
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
