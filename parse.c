#include "asm.h"

void	get_opcode(t_opcode *opcode, int h, int i, char *line)
{
	opcode->name = ft_strsub(line, h, i - h);
	if (!search_struct(opcode->name))
		show_error();
	opcode->codage = search_struct(opcode->name)->coding_byte;
	opcode->nb_param = search_struct(opcode->name)->nb_param;
	opcode->opcode = search_struct(opcode->name)->opcode;
	get_params(opcode, i, line);
	if (!is_valid_param(opcode))
		show_error();
}

void	parse_instr(t_opcode **ohead, t_label **lhead, char *line)
{
	int			i;
	int			h;
	t_opcode	*opcode;

	i = 0;
	opcode = create_opcode();
	opcode->label = *lhead;
	*lhead = NULL;
	ft_lstaddendopcode(ohead, opcode);
	while (line[i] && ft_isws(line[i]))
		i++;
	h = i;
	while (line[i] && !ft_isws(line[i]) && line[i] != LABEL_CHAR)
		i++;
	if (line[i] == LABEL_CHAR)
	{
		i++;
		while (line[i] && ft_isws(line[i]))
			i++;
		h = i;
		while (line[i] && !ft_isws(line[i]))
			i++;
		get_opcode(opcode, h, i, line);
	}
	else
		get_opcode(opcode, h, i, line);
}

int	get_label(t_label **lhead, char *line)
{
	t_label		*item;
	int			i;
	int			h;	

	i = 0;
	while (line[i] && ft_isws(line[i]))
		i++;
	h = i;
	while (line[i] && !ft_isws(line[i]) && line[i] != LABEL_CHAR)
		i++;
	if (line[i] == LABEL_CHAR)
	{
		item = create_label();
		item->name = ft_strsub(line, h, i-h);
		if (!is_valid_label(item->name))
			show_error();
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

	lhead = NULL;
	while (get_next_line(fd, &line))
	{
		if (line[0] != '\0' && line[0] != COMMENT_CHAR && !ft_isempty(line))
		{
			clear_comment(line);
			if (get_label(&lhead, line))
				parse_instr(ohead, &lhead, line);
		}
	}
}

