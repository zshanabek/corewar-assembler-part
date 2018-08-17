/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pr_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zshanabe <zshanabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 12:05:34 by vradchen          #+#    #+#             */
/*   Updated: 2018/08/14 16:54:59 by zshanabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_pr_param1(t_param *p)
{
	if (p->type == 1)
		ft_printf(1, "r%-17s", p->ival_str);//lld", p->ival_str);
	else if (p->type == 2)
	{
		if (p->sval == NULL)
			ft_printf(1, "%%%-17s", p->ival_str);//lld", p->ival);
		else
			ft_printf(1, "%%:%-16s", p->sval);
	}
	else if (p->type == 3)
	{
		if (p->sval == NULL)
			ft_printf(1, "%-18s", p->ival_str);//lld", p->ival);
		else
			ft_printf(1, ":%-17s", p->sval);
	}
}

char		*ft_short(int i)
{
	char	*ret;
	char	*hex;

	ret = ft_console(i);
	hex = ft_itoa_base(ft_atoi_base(ret, 2), 16);
	ft_strdel(&ret);
	return (hex);
}

void		ft_short2(char *hex, int i, int space)
{
	char	*two;

	while (ft_strlen(hex) < 8)
		hex = ft_arg_join(ft_strdup("0"), hex, 3);
	two = ft_strnew(2);
	while (i != 8)
	{
		two[0] = hex[i];
		two[1] = hex[i + 1];
		ft_printf(1, "%-4i", ft_atoi_base(two, 16));
		i += 2;
	}
	if (space == 4)
		ft_printf(1, "%2s", " ");
	else if (space == 2)
		ft_printf(1, "%10s", " ");
	ft_strdel(&two);
	ft_strdel(&hex);
}

void		ft_pr_param2(t_param *p, t_opcode *in, t_opcode *ohead)
{
	char	*hex;

	if (p->type == 1)
		ft_printf(1, "%-18i", p->ival);
	else
	{
		if (p->sval == NULL)
		{
			if (p->ival < 0)
				hex = ft_short(p->ival);
			else
				hex = ft_itoa_base(p->ival, 16);
		}
		else
		{
			if (ft_print_l2(ohead, in, p) < 0)
				hex = ft_short(ft_print_l2(ohead, in, p));
			else
				hex = ft_itoa_base(ft_print_l2(ohead, in, p), 16);
		}
		if (p->size == 4)
			ft_short2(hex, 0, 4);
		else if (p->size == 2)
			ft_short2(hex, 4, 2);
	}
}

void		ft_pr_param3(t_param *p, t_opcode *in, t_opcode *ohead)
{
	if (p->type == 1)
		ft_printf(1, "%-18i", p->ival);
	else
	{
		if (p->sval == NULL)
			ft_printf(1, "%-18i", p->ival);
		else
			ft_printf(1, "%-18i", ft_print_l2(ohead, in, p));
	}
}
