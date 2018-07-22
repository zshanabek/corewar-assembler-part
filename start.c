#include "asm.h"

static void	write_magic(int fd)
{
	long	magic;

	magic = COREWAR_EXEC_MAGIC;
	magic = ((magic >> 24) & 0xff) | ((magic << 8) & 0xff0000) |
		((magic >> 8) & 0xff00) | ((magic << 24) & 0xff000000);
	write(fd, &magic, 4);
}

char 	*get_name(char *line, int fd)
{
	char		*name;
	char		**arr;

	get_next_line(fd, &line);
	if (ft_strstr(line, NAME_CMD_STRING))
	{
		arr = ft_strsplit(line, '"');
		if (ft_2darrlen(arr) == 2 && ft_strequ(ft_strtrim(arr[0]), NAME_CMD_STRING))
		{
			name = ft_strnew(PROG_NAME_LENGTH);
			ft_bzero(name, PROG_NAME_LENGTH);
			ft_strcpy(name, arr[1]);
			return (name);
		}
		else
			return (0);
	}
	else
		return (0);
}

char	*get_comment(char *line, int fd)
{
	char		*comment;
	char		**arr;

	get_next_line(fd, &line);
	if (ft_strstr(line, COMMENT_CMD_STRING))
	{
		arr = ft_strsplit(line, '"');
		if (ft_2darrlen(arr) == 2 && ft_strequ(ft_strtrim(arr[0]), COMMENT_CMD_STRING))
		{
			comment = ft_strnew(COMMENT_LENGTH);
			ft_bzero(comment, COMMENT_LENGTH);
			ft_strcpy(comment, arr[1]);
			return (comment);
		}
		else
			return (0);
	}
	else
		return (0);
}

int main(int ac, char **av)
{
	int		fd;
	int		fd2;
	char	*line;
	char 	*name;
	char 	*comment;	

	line = NULL;
	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./asm test\n", 2);
		exit(1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit(1);
	name = get_name(line, fd);
	comment	= get_comment(line, fd);	
	get_next_line(fd, &line);
	get_next_line(fd, &line);
	if (name == 0 || comment == 0)
		exit(1);
	fd2 = open("mbappe.cor", O_WRONLY | O_CREAT | O_TRUNC, 0644);		
	write_magic(fd2);
	write(fd2, name, PROG_NAME_LENGTH);
	write(fd2, comment, COMMENT_LENGTH);
}