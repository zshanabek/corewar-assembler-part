#include "asm.h"

int is_label_char(char c)
{
	int i;

	i = 0;
	while (LABEL_CHARS[i])
	{
		if (LABEL_CHARS[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void 	get_params(t_opcode *opcode, int i, char *line)
{
	char *params;
	char **arr;
	int k;

	params = ft_strsub(line, i, ft_strlen(line) - i);
	arr = ft_strsplit(params, ',');
	k = 0;
	while (arr[k])
	{
		arr[k] = ft_strtrim(arr[k]);
		k++;
	}
	ft_print2darr(arr);
}

void	get_opcode(t_opcode *opcode, int h, int i, char *line)
{
	opcode->name = ft_strsub(line, h, i - h);
	get_params(opcode, i, line);
}

t_label	*parse_instr(t_opcode **ohead, char *line)
{
	int			i;
	int			h;
	t_label		*label;
	t_opcode	*opcode;

	opcode = create_opcode();
	ft_lstaddendopcode(ohead, opcode);
	i = 0;
	while (line[i] && ft_isws(line[i]))
		i++;
	h = i;
	while (is_label_char(line[i]) && line[i] != LABEL_CHAR)
		i++;
	if (line[i] == LABEL_CHAR)
	{
		label = create_label();
		label->name = ft_strsub(line, h, i-h);
		ft_lstaddendlabel(&opcode->label, label);
		i++;
		while (line[i] && ft_isws(line[i]))
			i++;
		h = i;
		while (line[i] && is_label_char(line[i]))
			i++;
		get_opcode(opcode, h, i, line);
	}
	else
		get_opcode(opcode, h, i, line);
	return (label);
}

void	read_instr(int fd, char *line)
{
	t_opcode	*ohead;

	ohead = NULL;
	if (get_next_line(fd, &line))
		parse_instr(&ohead, line);
	iter_opcode(ohead, print_opcode);
}

