/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zshanabe <zshanabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 17:32:21 by vradchen          #+#    #+#             */
/*   Updated: 2018/08/14 17:32:03 by zshanabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			ft_print_l(t_opcode *instr, t_opcode *in, t_param *p, int fd2)
{
	t_opcode	*i;
	t_label		*l;
	int			x;

	i = instr;
	while (i)
	{
		l = i->label;
		while (l)
		{
			if (ft_strequ(l->name, p->sval))
			{
				x = ft_swp_bits(i->pos - in->pos, p->size);
				write(fd2, &x, p->size);
				return ;
			}
			l = l->next;
		}
		i = i->next;
	}
}

void			ft_param(t_opcode *in, t_opcode *instruct, int fd2)
{
	t_param		*p;
	int			x;

	p = in->param;
	while (p)
	{
		if (p->sval != NULL)
			ft_print_l(instruct, in, p, fd2);
		else
		{
			x = ft_swp_bits(p->ival, p->size);
			write(fd2, &x, p->size);
		}
		p = p->next;
	}
}

char			*ft_w(t_opcode *in)
{
	t_param		*p;
	char		*cod;

	cod = NULL;
	p = in->param;
	while (p)
	{
		if (p->type == 0)
			break ;
		else if (p->type == 1)
			cod = ft_arg_join(cod, ft_strdup("01"), 3);
		else if (p->type == 2)
			cod = ft_arg_join(cod, ft_strdup("10"), 3);
		else if (p->type == 3)
			cod = ft_arg_join(cod, ft_strdup("11"), 3);
		p = p->next;
	}
	while (ft_strlen(cod) < 8)
		cod = ft_arg_join(cod, ft_strdup("00"), 3);
	return (cod);
}

long			ft_b(char *bin)
{
	int		i;
	long	x;
	int		power;

	power = 1;
	x = 0;
	i = 7;
	while (i > -1)
	{
		x += (bin[i] - 48) * power;
		i--;
		power *= 2;
	}
	ft_strdel(&bin);
	return (x);
}

void			ft_write_in(t_opcode *instruct, int fd2)
{
	t_opcode	*in;
	long		x;

	in = instruct;
	if (in->opcode == -1)
		return ;
	while (in)
	{
		write(fd2, &in->opcode, 1);
		if (in->codage == 1)
		{
			x = ft_b(ft_w(in));
			write(fd2, &x, 1);
		}
		ft_param(in, instruct, fd2);
		in = in->next;
	}
}
