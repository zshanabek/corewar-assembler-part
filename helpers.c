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