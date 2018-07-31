#include "asm.h"

int is_valid_param(t_opcode *to_find)
{
	int		i;
	int		j;
	int		k;
	par_t	*elem;
	t_param	*cur;

	i = 0;
	k = 0;
	elem = search_param(to_find);
	cur = to_find->param;
	while (i < to_find->nb_param)
	{
		j = 0;
		while (j < 3)
		{
			if (elem->p[i][j] == cur->type)
				k++;
			j++;
		}
		i++;
		cur = cur->next;
	}
	if (k != to_find->nb_param)
		return (0);
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
	int		commas;

	str = ft_strsub(line, i, ft_strlen(line) - i);
	commas = count_commas(str);
	arr = ft_strsplit(str, SEPARATOR_CHAR);
	if (ft_2darrlen(arr) != commas + 1)
		show_error();
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
