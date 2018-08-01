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

void	analyze_param(t_param *item, char *str, int code, int type)
{
	char	*temp;

	if (code == DIR_CODE)
	{
		str = ft_strsub(str, 1, ft_strlen(str) - 1);
		if (str[0] == LABEL_CHAR)
            type = 2;
		else if (ft_isdigit(str[0]))
        	type = 1;
		else
			show_error();			
	}
	if (str[0] == LABEL_CHAR || code == REG_CODE)
		temp = ft_strsub(str, 1, ft_strlen(str) - 1);
	else
		temp = str;
	if (is_digital(temp) && type == 1)
		item->ival = ft_atoi(temp);
	else if (type == 2)
		item->sval = temp;
	else
		show_error();
	if (code == REG_CODE && item->ival > REG_NUMBER)
		show_error();
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

void	get_params(t_opcode *opcode, int i, char *line)
{
	int			k;
	char		**arr;
	t_param		*item;

	k = 0;
	arr = get_params_array(opcode, i, line);
	while (arr[k])
	{
		arr[k] = ft_strtrim(arr[k]);
		item = create_param();	
		if (arr[k][0] == 'r')
			analyze_param(item, arr[k], REG_CODE, 1);
		else if (arr[k][0] == DIRECT_CHAR)
			analyze_param(item, arr[k], DIR_CODE, 0);
		else if (ft_isdigit(arr[k][0]))
			analyze_param(item, arr[k], IND_CODE, 1);
		else if (arr[k][0] == LABEL_CHAR)
			analyze_param(item, arr[k], IND_CODE, 2);
		else
			show_error();
		ft_lstaddendpar(&opcode->param, item);
		k++;
	}
}
