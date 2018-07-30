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