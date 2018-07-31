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

par_t	*search_param(t_opcode *elem)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		if (ft_strequ(info[i].name, elem->name))
			return (&info[i]);
		i++;
	}
	return (0);
}

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