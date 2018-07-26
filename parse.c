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

int		is_digital(char *line)
{
	int i;

	i = 0;
	if (line == NULL)
		return (0);
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

void 	get_params(t_opcode *opcode, int i, char *line)
{
	char *str;
	char **arr;
	int k;
	t_param *item;
	char *temp;

	str = ft_strsub(line, i, ft_strlen(line) - i);
	arr = ft_strsplit(str, ',');
	k = 0;
	while (arr[k])
	{
		arr[k] = ft_strtrim(arr[k]);
		item = create_param();
		if (arr[k][0] == 'r')
		{
			temp = ft_strsub(arr[k], 1, ft_strlen(arr[k]) - 1);
			if (is_digital(temp))
			{
				item->ival = ft_atoi(temp);
				item->type = REG_CODE;				
			}
		}
		else if (arr[k][0] == '%')
		{
			item->type = DIR_CODE;
			if (arr[k][1] == ':')
			{
				temp = ft_strsub(arr[k], 2, ft_strlen(arr[k]) - 2);
				item->sval = temp;			
			}
			else
			{
				temp = ft_strsub(arr[k], 1, ft_strlen(arr[k]) - 1);				
				if (is_digital(temp))
					item->ival = ft_atoi(temp);					
			}
		}
		else if (ft_isdigit(arr[k][0]) || arr[k][0] == ':')
		{
			if (arr[k][0] == ':')
				temp = ft_strsub(arr[k], 1, ft_strlen(arr[k]) - 1);				
			else
				temp = arr[k];			
			if (is_digital(temp))
				item->ival = ft_atoi(temp);
		}
		else
			show_error();
		ft_lstaddendpar(&opcode->param, item);
		k++;
	}
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

