/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zshanabe <zshanabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 11:12:22 by vradchen          #+#    #+#             */
/*   Updated: 2018/08/13 15:49:37 by zshanabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	get_opcode(t_opcode *opcode, int i, int n, char *line)
{
	char	**arr;
	t_op	*elem;
	t_param	*cur;

	arr = get_params_array(i, n, line);
	get_params(opcode, arr, n);
	if (!search_struct(opcode->name))
		show_error(3, n, 0, opcode->name);
	opcode->codage = search_struct(opcode->name)->coding_byte;
	opcode->nb_param = search_struct(opcode->name)->nb_param;
	opcode->opcode = search_struct(opcode->name)->opcode;
	elem = search_struct(opcode->name);
	cur = opcode->param;
	is_valid_param(elem, cur, opcode->name);
	if (ft_2darrlen(arr) != opcode->nb_param)
		show_error(5, 0, 0, opcode->name);
	ft_del2darr(arr);
}

void	parse_instr(t_opcode **ohead, t_label **lhead, int n, char *line)
{
	int			i;
	int			h;
	t_opcode	*elem;

	i = 0;
	elem = create_opcode(n);
	elem->label = *lhead;
	*lhead = NULL;
	ft_lstaddendopcode(ohead, elem);
	get_i_h(&i, &h, line);
	if (line[i] == LABEL_CHAR)
	{
		i++;
		get_i_h(&i, &h, line);
		elem->name = ft_strsub(line, h, i - h);
		get_opcode(elem, i, n, line);
	}
	else
	{
		elem->name = ft_strsub(line, h, i - h);
		get_opcode(elem, i, n, line);
	}
}

int		get_label(t_label **lhead, int n, char *line)
{
	int			i;
	int			h;
	t_label		*item;

	i = 0;
	get_i_h(&i, &h, line);
	if (line[i] == LABEL_CHAR)
	{
		item = create_label();
		item->name = ft_strsub(line, h, i - h);
		if (!ft_strcmp(item->name, "\0") || !is_valid_label(item->name))
			show_error(6, n, 0, "");
		ft_lstaddendlabel(lhead, item);
	}
	else
		return (1);
	i++;
	while (line[i] && ft_isws(line[i]))
		i++;
	if (line[i] == '\0')
		return (0);
	return (1);
}

void	read_instr(int fd, int *n, t_opcode **ohead)
{
	char		*line;
	t_label		*lhead;
	t_opcode	*item;

	lhead = NULL;
	while (get_next_line(fd, &line))
	{
		(*n)++;
		clear_comment(line);
		if (line[0] != '\0' && line[0] != COMMENT_CHAR && !ft_isempty(line))
		{
			if (get_label(&lhead, *n, line))
				parse_instr(ohead, &lhead, *n, line);
		}
		ft_strdel(&line);
	}
	if (lhead != NULL)
	{
		item = create_opcode(*n);
		item->label = lhead;
		ft_lstaddendopcode(ohead, item);
		if (!detect_blank_line(fd))
			show_error(7, *n, 0, "");
	}
	(*n)++;
}
