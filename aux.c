#include "asm.h"

int		count_commas(char *str)
{
	int		i;
	int		count;	

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == SEPARATOR_CHAR)
			count++;			
		i++;
	}
	return (count);
}