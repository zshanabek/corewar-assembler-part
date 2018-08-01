#include "asm.h"

t_op	*search_struct(char *name)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (ft_strequ(op_tab[i].name, name))
			return (&op_tab[i]);					
		i++;
	}
	return (0);
}

int		is_label_char(char c)
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

int		is_valid_label(char *str)
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

void	clear_comment(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ';' || line[i] == COMMENT_CHAR)
		{
			while (line[i])
			{
				line[i] = '\0';
				i++;
			}
		}
		i++;
	}
}
