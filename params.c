#include "asm.h"

void	is_valid_param(t_op *elem, t_param *cur, int nb, char *name)
{
	int		i;
	int		j;
	int		k;
	char	**massiv;

	massiv = malloc(sizeof(char *) * 3);
	massiv[0] = ft_strdup("reg");
	massiv[1] = ft_strdup("direct");
	massiv[2] = ft_strdup("indirect");
	i = 0;
	k = 0;
	while (i < nb && cur != NULL)
	{
		j = 0;
		while (j < 3)
		{
			if (elem->param[i][j] == cur->type)
				k = 1;
			j++;
		}
		if (k == 0)
			exit(ft_printf("Invalid param %d type %s for command %s\n", i, 
			massiv[cur->type - 1], name));						
		k = 0;
		i++;
		cur = cur->next;
	}
	ft_del2darr(massiv);
}

int		analyze_type(t_param *item, char *temp, int type, int code)
{
	if (is_digital(temp) && type == 1)
		item->ival = ft_atoi(temp);
	else if (type == 2)
		item->sval = temp;
	else
		return (0);
	if (code == REG_CODE && (item->ival > REG_NUMBER || item->ival < 0))
		return (0);	
	item->type = code;
	return (1);
}

int		analyze_param(t_param *item, char *str, int code, int type)
{
	char	*temp;
	char	*buf;

	if (str[1] == '\0' && code != IND_CODE)
		return (0);
	if (code == DIR_CODE)
	{
		temp = ft_strsub(str, 1, ft_strlen(str) - 1);
		str = temp;
		free(temp);
		if (str[0] == LABEL_CHAR)
            type = 2;
		else if (ft_isdigit(str[0]) || (str[0] == '-' && ft_isdigit(str[1])))
        	type = 1;
		else
			return (0);
	}
	if (str[0] == LABEL_CHAR || code == REG_CODE)
	{
		buf = ft_strsub(str, 1, ft_strlen(str) - 1);
		temp = buf;
		free(temp);
	}
	else
		temp = str;
	if (!analyze_type(item, temp, type, code))
		return (0);
	return (1);
}

char	**get_params_array(t_opcode *opcode, int i, int n, char *line)
{
	char	*str;
	char	**arr;
	int		commas;

	str = ft_strsub(line, i, ft_strlen(line) - i);
	commas = count_commas(str);
	arr = ft_strsplit(str, SEPARATOR_CHAR);
	if (ft_2darrlen(arr) <= 0 || ft_isempty(str))
		exit(ft_printf("No parameters for opcode \"%s\"\n", opcode->name));
	if (ft_2darrlen(arr) != commas + 1)
		exit(ft_printf("Syntax error at [%d] SEPARATOR \",\"\n", n));
	free(str);
	return (arr);
}

void	get_params(t_opcode *opcode, char **arr, int n)
{
	int 		e;	
	int			k;
	char 		*temp;
	t_param		*item;

	e = 1;
	k = 0;
	while (arr[k])
	{
		temp = ft_strtrim(arr[k]);
		item = create_param();	
		if (temp[0] == 'r')
			e = analyze_param(item, temp, REG_CODE, 1);
		else if (temp[0] == DIRECT_CHAR)
			e = analyze_param(item, temp, DIR_CODE, 0);
		else if (ft_isdigit(temp[0]) || (temp[0] == '-' && ft_isdigit(temp[1])))
			e = analyze_param(item, temp, IND_CODE, 1);
		else if (temp[0] == LABEL_CHAR)
			e = analyze_param(item, temp, IND_CODE, 2);
		ft_lstaddendpar(&opcode->param, item);
		if (e == 0)
			exit(ft_printf("Syntax error at [%03d] INSTRUCTION \"%s\"\n",
			n, temp));
		free(temp);		
		k++;
	}
}
