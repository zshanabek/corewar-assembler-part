#include "asm.h"

int	ft_gnl(int fd, char **s)
{
	int i;

	ft_strdel(s);
	i = get_next_line(fd, s);
	return (i);
}