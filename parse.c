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

int is_valid_label(char *str)
{
	int i;
	int flag;

	flag = 0;
	i = 0;
	while (str[i])
	{
		if (is_label_char(str[i]))
			flag = 1;
		if (flag == 0)
			return (0);
		flag = 0;
		i++;
	}
	return (1);
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

void get_param(t_param *item, char *str, int code)
{
	char *temp;

	if (str[0] == LABEL_CHAR || code == REG_CODE)
		temp = ft_strsub(str, 1, ft_strlen(str) - 1);
	else
		temp = str;
	if (!is_digital(temp) || (LABEL_CHAR == str[0] && code == IND_CODE))
		item->sval = temp;
	else
		item->ival = ft_atoi(temp);
	item->type = code;	
}

char	**get_params_array(t_opcode *opcode, int i, char *line)
{
	char	*str;
	char	**arr;

	str = ft_strsub(line, i, ft_strlen(line) - i);
	arr = ft_strsplit(str, SEPARATOR_CHAR);
	if (ft_2darrlen(arr) != opcode->nb_param)
		show_error();
	return (arr);
}

void 	get_params(t_opcode *opcode, int i, char *line)
{
	int			k;
	char		*temp;
	char		**arr;
	t_param		*item;

	k = 0;
	arr = get_params_array(opcode, i, line);
	while (arr[k])
	{
		arr[k] = ft_strtrim(arr[k]);
		item = create_param();
		if (arr[k][0] == 'r')
			get_param(item, arr[k], REG_CODE);
		else if (arr[k][0] == DIRECT_CHAR)
		{
			temp = ft_strsub(arr[k], 1, ft_strlen(arr[k]) - 1);
			get_param(item, temp, DIR_CODE);
		}
		else if (ft_isdigit(arr[k][0]) || arr[k][0] == LABEL_CHAR)
			get_param(item, arr[k], IND_CODE);
		else
			show_error();
		ft_lstaddendpar(&opcode->param, item);
		k++;
	}
}

void	get_opcode(t_opcode *opcode, int h, int i, char *line)
{
	opcode->name = ft_strsub(line, h, i - h);
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

