#include "asm.h"

int main()
{
	char *line;

	line = NULL;
	while (get_next_line(0, &line))
	{
		ft_printf("%s\n", line);
	}
}