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

int		is_valid_param(t_opcode *elem)
{
	int		i;
	int		j;	
	t_param	*cur;

	i = 0;
	j = 0;
	while (i < 16)
	{
		if (ft_strequ(info[i].name, elem->name))
		{
			i = 0;			
			cur = elem->param;
			while (j < 3)
			{

				j++;
			}
		}
		i++;
	}
	return (0);
}

void	clear_comment(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ';' || line[i] == '#')
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