#include "asm.h"

void	is_valid_param(t_op *elem, t_param *cur, int nb, char *name)
{
	int		i;
	int		j;
	int		k;
	char	*massiv[3];

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
			exit(ft_printf("Invalid parameter %d type %s for instruction \"%s\"\n", i, massiv[cur->type - 1], name));						
		k = 0;
		i++;
		cur = cur->next;
	}
}

void	analyze_type(t_param *item, char *temp, int type, int code)
{
	if (is_digital(temp) && type == 1)
		item->ival = ft_atoi(temp);
	else if (type == 2)
		item->sval = temp;
	else
		exit(ft_printf("Invalid param\n"));
	if (code == REG_CODE && (item->ival > REG_NUMBER || item->ival < 0))
		exit(ft_printf("t_dir value must be between 0 and 16\n"));
	item->type = code;
}

void	analyze_param(t_param *item, char *str, int code, int type)
{
	char	*temp;

	temp = NULL;
	if (str[1] == '\0' && code != IND_CODE)
		exit(ft_printf("Invalid param\n"));
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
			exit(ft_printf("Invalid t_dir\n"));
	}
	if (str[0] == LABEL_CHAR || code == REG_CODE)
		temp = ft_strsub(str, 1, ft_strlen(str) - 1);
	else
		temp = str;
	analyze_type(item, temp, type, code);
}

char	**get_params_array(t_opcode *opcode, int i, char *line)
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
		exit(ft_printf("Too many commas\n"));
	if (ft_2darrlen(arr) != opcode->nb_param)
		exit(ft_printf("Wrong number of parameters for opcode \"%s\"\n", opcode->name));
	free(str);
	return (arr);
}

void	get_params(t_opcode *opcode, char **arr)
{
	int			k;
	char 		*temp;
	t_param		*item;

	k = 0;
	while (arr[k])
	{
		temp = ft_strtrim(arr[k]);
		item = create_param();	
		if (temp[0] == 'r')
			analyze_param(item, temp, REG_CODE, 1);
		else if (temp[0] == DIRECT_CHAR)
			analyze_param(item, temp, DIR_CODE, 0);
		else if (ft_isdigit(temp[0]) || (temp[0] == '-' && ft_isdigit(temp[1])))
			analyze_param(item, temp, IND_CODE, 1);
		else if (temp[0] == LABEL_CHAR)
			analyze_param(item, temp, IND_CODE, 2);
		else
			exit(ft_printf("Invalid parameter\n"));
		ft_lstaddendpar(&opcode->param, item);
		free(temp);
		k++;
	}
}
