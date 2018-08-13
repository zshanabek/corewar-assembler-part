/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zshanabe <zshanabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 11:47:01 by vradchen          #+#    #+#             */
/*   Updated: 2018/08/13 16:45:07 by zshanabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char			*ft_console2(int v)
{
	char	*ret;
	int		i;
	int		value;

	value = v;
	ret = ft_itoa_base(value, 2);
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
	return (ret);
}

char			*ft_console(int v)
{
	char	*ret;
	int		i;

	ret = ft_console2(v);
	i = ft_strlen(ret) - 1;
	while (i > -1)
	{
		if (ret[i] == '0')
		{
			ret[i] = '1';
			break ;
		}
		else
			ret[i] = '0';
		if (i == 0)
		{
			ret = ft_arg_join("1", ret, 3);
			break ;
		}
		i--;
	}
	return (ret);
}

int				ft_print_l2(t_opcode *instr, t_opcode *in, t_param *p)
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
				return (i->pos - in->pos);
			l = l->next;
		}
		i = i->next;
	}
	return (0);
}

void			ft_print_flag2(t_opcode *in, t_opcode *ohead)
{
	t_param		*p;

	ft_printf2("\n%-5i(%-3i) :        %-10s", in->pos, in->size,
		g_op[in->opcode - 1].name);
	p = in->param;
	while (p)
	{
		ft_pr_param1(p);
		p = p->next;
	}
	if (in->codage == 1)
		ft_printf2("\n% 20s%-4lld%-6lld", " ", in->opcode, ft_bin_to(ft_w(in)));
	else
		ft_printf2("\n% 20s%-4lld%6s", " ", in->opcode, " ");
	p = in->param;
	while (p)
	{
		ft_pr_param2(p, in, ohead);
		p = p->next;
	}
	ft_printf2("\n                    %-4lld", in->opcode);
	if (in->codage == 1)
		ft_printf2("%-6lld", ft_bin_to(ft_w(in)));
	else
		ft_printf2("%6s", " ");
}

void			ft_print_flag(t_opcode *in, t_opcode *ohead)
{
	t_label	*l;
	t_param	*p;

	l = in->label;
	while (l)
	{
		ft_printf2("\n%-11i:    %s:", in->pos, l->name);
		l = l->next;
	}
	if (in->opcode == -1)
	{
		ft_printf2("\n");
		return ;
	}
	ft_print_flag2(in, ohead);
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
