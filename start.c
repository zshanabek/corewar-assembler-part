#include "asm.h"

void	get_name(char *line, int fd2)
{
	int			i;
	char		*name;
	char		*temp;
	char		**arr;
	static int	flag;

	i = 0;
	if (flag == 0 && ft_strstr(line, ".name"))
	{
		arr = ft_strsplit(line, ' ');
		i = 1;
		while (arr[1] && arr[1][i] != '"')
			i++;
		long magic = 0xEA83F3;
		write(fd2, &magic, 4);
		name = ft_strnew(132);
		ft_bzero(name, ft_strlen(name));
		temp = ft_strsub(arr[1], 1, i-1);
		ft_strcpy(name, temp);
		write(fd2, name, 132);
		flag = 1;
	}
}

int main(int ac, char **av)
{
	char *line;
	char ch;
	int fd;
	int fd2;

	line = NULL;
	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./asm test\n", 2);
		exit(1);
	}
	fd = open(av[1], O_RDONLY);
	fd2 = open("mbappe.cor", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (get_next_line(fd, &line))
	{
		get_name(line, fd2);
		free(line);
	}
}