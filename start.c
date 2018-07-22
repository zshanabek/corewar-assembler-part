#include "asm.h"

void	get_name(char *line, int *flag, int fd2)
{
	int			i;
	long		magic;
	char		*name;
	char		**arr;

	if (*flag == 0 && ft_strstr(line, NAME_CMD_STRING))
	{
		i = 0;		
		arr = ft_strsplit(line, '"');
		if (ft_2darrlen(arr) == 2 && ft_strequ(ft_strtrim(arr[0]), NAME_CMD_STRING))
		{
			magic = COREWAR_EXEC_MAGIC;
			write(fd2, &magic, 4);
			name = ft_strnew(PROG_NAME_LENGTH);
			ft_bzero(name, PROG_NAME_LENGTH);
			ft_strcpy(name, arr[1]);
			write(fd2, name, PROG_NAME_LENGTH);
		}
	}
	*flag = 1;	
}

void	get_comment(char *line, int *flag, int fd2)
{
	int			i;
	char		*comment;
	char		**arr;

	if (*flag == 1 && ft_strstr(line, COMMENT_CMD_STRING))
	{
		i = 0;		
		arr = ft_strsplit(line, '"');
		ft_printf("ok: %d\n", ft_2darrlen(arr));		
		if (ft_2darrlen(arr) == 2 && ft_strequ(ft_strtrim(arr[0]), COMMENT_CMD_STRING))
		{
			comment = ft_strnew(COMMENT_LENGTH);
			ft_bzero(comment, COMMENT_LENGTH);
			ft_strcpy(comment, arr[1]);
			write(fd2, comment, COMMENT_LENGTH);
		}
	}
	*flag = 2;			
}

int main(int ac, char **av)
{
	int		fd;
	int		fd2;
	char	*line;
	int		i;

	line = NULL;
	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./asm test\n", 2);
		exit(1);
	}
	fd = open(av[1], O_RDONLY);
	fd2 = open("mbappe.cor", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit(1);
	i = 0;
	while (get_next_line(fd, &line))
	{
		get_name(line, &i, fd2);
		get_comment(line, &i, fd2);
		free(line);
	}
}