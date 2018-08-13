/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zshanabe <zshanabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 21:42:20 by zshanabe          #+#    #+#             */
/*   Updated: 2018/08/12 21:05:47 by zshanabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	is_valid_param(t_op *elem, t_param *cur, char *name)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (cur != NULL)
	{
		j = 0;
		while (j < 3)
		{
			if (elem->param[i][j] == cur->type)
				k = 1;
			j++;
		}
		if (k == 0)
			show_error(4, i, cur->type - 1, name);
		k = 0;
		i++;
		cur = cur->next;
	}
}

void	get_i_h(int *i, int *h, char *line)
{
	while (line[*i] && ft_isws(line[*i]))
		(*i)++;
	(*h) = (*i);
	while (line[*i] && !ft_isws(line[*i]) && line[*i] != LABEL_CHAR)
		(*i)++;
}

void	print_label(t_label *label)
{
	ft_printf("{blue}   %s{eoc}\n", label->name);
}

void	print_param(t_param *param)
{
	if (param->sval != NULL)
		ft_printf("   sval: %s\n", param->sval);
	ft_printf("   ival: {yellow}%d{eoc}\n", param->ival);
	ft_printf("   type: %d\n", param->type);
	if (param->next != NULL)
		ft_printf("--------------\n");
}

void	print_opcode(t_opcode *opcode)
{
	ft_printf("name: {magenta}%s{eoc}\n", opcode->name);
	if (opcode->label != NULL)
	{
		ft_printf("labels:\n");
		iter_label(opcode->label, print_label);
	}
	if (opcode->param != NULL)
	{
		ft_printf("params:\n");
		iter_param(opcode->param, print_param);
	}
	ft_printf("////////////////\n");
}

char	**get_array(int n, int a, char *str)
{
	char	**mrr;

	mrr = malloc(sizeof(char *) * 4);
	mrr[0] = ft_strdup("reg");
	mrr[1] = ft_strdup("direct");
	mrr[2] = ft_strdup("indirect");
	mrr[3] = NULL;
	ft_printf("Invalid parameter %d type %s for \
		instruction %s\n", n, mrr[a], str);
	ft_del2darr(mrr);
	return (mrr);
}

void	show_error(int type, int n, int a, char *str)
{
	if (type == 0)
		printf("Syntax error at token [%03d] INSTRUCTION %s\n", n, str);
	else if (type == 1)
		ft_printf("Syntax error at token [%03d] SEPARATOR \",\"\n", n);
	else if (type == 2)
		ft_printf("Syntax error at token [%03d] ENDLINE\n", n);
	else if (type == 3)
		ft_printf("Invalid instruction at token [%03d] "
		"INSTRUCTION \"%s\"\n", n, str);
	else if (type == 4)
		get_array(n, a, str);
	else if (type == 5)
		ft_printf("Invalid parameter count for instruction \"%s\"\n", str);
	else if (type == 6)
		ft_printf("Lexical error at [%d]\n", n);
	else if (type == 7)
		ft_printf("Syntax error at token [%03d] END \"(null)\"\n", n);
	else if (type == 8)
		ft_printf("No such label %s while attempting to dereference "
		"token [%03d] DIRECT_LABEL \"%%:%s\"\n", str, n, str);
	exit(1);
}