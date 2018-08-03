#include "asm.h"

void	get_opcode(t_opcode *opcode, int h, int i, char *line)
{
	char **arr;

	opcode->name = ft_strsub(line, h, i - h);
	if (!search_struct(opcode->name))
		exit(ft_printf("There is no instruction with such name: %s\n", opcode->name));
	opcode->codage = search_struct(opcode->name)->coding_byte;
	opcode->nb_param = search_struct(opcode->name)->nb_param;
	opcode->opcode = search_struct(opcode->name)->opcode;
	arr = get_params_array(opcode, i, line);
	get_params(opcode, arr);
	ft_del2darr(arr);	
	if (!is_valid_param(opcode))
		exit(ft_printf("Invalid parameter\n"));
}

void	get_i_h(int *i, int *h, char *line)
{
	while (line[*i] && ft_isws(line[*i]))
		(*i)++;
	(*h) = (*i);
	while (line[*i] && !ft_isws(line[*i]) && line[*i] != LABEL_CHAR)
		(*i)++;
}

void	parse_instr(t_opcode **ohead, t_label **lhead, char *line)
{
	int			i;
	int			h;
	t_opcode	*elem;

	i = 0;
	elem = create_opcode();
	elem->label = *lhead;
	*lhead = NULL;
	ft_lstaddendopcode(ohead, elem);
	get_i_h(&i, &h, line);
	if (line[i] == LABEL_CHAR)
	{
		i++;
		get_i_h(&i, &h, line);
		get_opcode(elem, h, i, line);
	}
	else
		get_opcode(elem, h, i, line);
}

int	get_label(t_label **lhead, char *line)
{
	int			i;
	int			h;	
	t_label		*item;

	i = 0;
	get_i_h(&i, &h, line);
	if (line[i] == LABEL_CHAR)
	{
		item = create_label();
		item->name = ft_strsub(line, h, i-h);
		if (!ft_strcmp(item->name, "\0"))
			exit(ft_printf("No label\n"));
		if (!is_valid_label(item->name))
			exit(ft_printf("Invalid label: %s\n", item->name));
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

void	read_instr(int fd, char *line, t_opcode **ohead)
{
	t_label 	*lhead;
	t_opcode 	*item;	

	lhead = NULL;
	while (get_next_line(fd, &line))
	{
		clear_comment(line);
		if (line[0] != '\0' && line[0] != COMMENT_CHAR && !ft_isempty(line))
		{
			if (get_label(&lhead, line))
				parse_instr(ohead, &lhead, line);
		}
		free(line);
	}
	if (lhead != NULL && *ohead == NULL)
	{
		item = create_opcode();
		item->label = lhead;
		ft_lstaddendopcode(ohead, item);
	}
}
