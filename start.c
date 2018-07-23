#include "asm.h"

static void	write_magic(int fd)
{
	long	magic;

	magic = COREWAR_EXEC_MAGIC;
	magic = ((magic >> 24) & 0xff) | ((magic << 8) & 0xff0000) |
		((magic >> 8) & 0xff00) | ((magic << 24) & 0xff000000);
	write(fd, &magic, 4);
}

void	ft_read_header(header_t *h, int fd)
{
	char	**arr;
	char	*str;

	h->magic = COREWAR_EXEC_MAGIC;
	get_next_line(fd, &str);
	arr = ft_strsplit(str, '"');
	if (arr[2] != NULL)
		exit(ft_printf("ERROR4\n"));
	if (ft_strequ(ft_strtrim(arr[0]), NAME_CMD_STRING))
		ft_strcpy(h->prog_name, arr[1]);
	get_next_line(fd, &str);
	arr = ft_strsplit(str, '"');
	if (ft_strequ(ft_strtrim(arr[0]), COMMENT_CMD_STRING))
		ft_strcpy(h->comment, arr[1]);
	else
		exit(ft_printf("ERROR3\n"));
}

void	get_instr(char *line)
{
	int i;
	char *label;

	label = NULL;
	i = 0;
	while (line[i] && line[i] != LABEL_CHAR)
		i++;
	if (line[i] != LABEL_CHAR)
		exit(1);
	label = ft_strsub(line, 0, i);
	ft_printf("%s\n", label);
}

int main(int ac, char **av)
{
	int		fd;
	int		fd2;
	char	*line;
	header_t	*h;

	line = NULL;
	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./asm test\n", 2);
		exit(1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit(1);
	h = malloc(sizeof(header_t));
	ft_read_header(h, fd);
	get_next_line(fd, &line);
	get_next_line(fd, &line);
	fd2 = open("mbappe.cor", O_WRONLY | O_CREAT | O_TRUNC, 0644);		
	write_magic(fd2);
	write(fd2, h->prog_name, PROG_NAME_LENGTH);
	write(fd2, h->comment, COMMENT_LENGTH);
	get_instr(line);
}