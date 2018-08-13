/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zshanabe <zshanabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 12:23:47 by vradchen          #+#    #+#             */
/*   Updated: 2018/08/13 16:45:54 by zshanabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_param_len(t_opcode *in, t_param *p)
{
	if (p->type == 0)
		return (0);
	else if (p->type == 1)
		return (1);
	else if (p->type == 2 && in->lab_size == 4)
		return (4);
	else
		return (2);
}

int		ft_check2(char *name, t_opcode *instr)
{
	t_opcode	*in;
	t_label		*l;

	in = instr;
	if (!name)
		return (1);
	while (in)
	{
		l = in->label;
		while (l)
		{
			if (ft_strequ(l->name, name))
				return (1);
			l = l->next;
		}
		in = in->next;
	}
	return (0);
}

void	ft_check_label(t_opcode *instr)
{
	t_opcode	*in;
	t_param		*p;

	in = instr;
	while (in)
	{
		p = in->param;
		while (p)
		{
			if (!ft_check2(p->sval, instr))
				show_error(8, in->n, 0, p->sval);
			p = p->next;
		}
		in = in->next;
	}
}

void	ft_hex2(t_opcode *in)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		if (ft_strequ(in->name, g_op[i].name))
		{
			in->opcode = g_op[i].opcode;
			in->codage = g_op[i].coding_byte;
			if (g_op[i].two_bytes == 1)
				in->lab_size = 2;
			else
				in->lab_size = 4;
			break ;
		}
		i++;
	}
	if (in->opcode != -1)
		in->size++;
	if (in->codage == 1)
		in->size++;
}

void	ft_h(t_opcode *instr, int n)
{
	int			len;
	t_opcode	*in;
	t_param		*p;

	len = 0;
	in = instr;
	if (instr == NULL)
		show_error(7, n, 0, "");
	while (in)
	{
		in->pos = len;
		ft_hex2(in);
		p = in->param;
		while (p)
		{
			p->size = ft_param_len(in, p);
			in->size += p->size;
			p = p->next;
		}
		len += in->size;
		in = in->next;
	}
	ft_check_label(instr);
}
