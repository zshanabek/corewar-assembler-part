#include "asm.h"

static void	write_magic(int fd)
{
	long	magic;

	magic = COREWAR_EXEC_MAGIC;
	magic = ((magic >> 24) & 0xff) | ((magic << 8) & 0xff0000) |
		((magic >> 8) & 0xff00) | ((magic << 24) & 0xff000000);
	write(fd, &magic, 4);
}

void	ft_fill_info(char *answer, int fd, char *str, int max)
{
	int		i;
	int		len;
	char	*s;

	i = 0;
	len = 1;
	if (str[i] != '\"')
		exit(ft_printf("ERROR1\n"));
	s = ft_strdup(str + 1);
	while (s[i] && s[i++] != '\"')
	{
		len++;
		if (s[i] == '\0' || s[i] == '\"')
		{
			if (len++ > max)
				exit(ft_printf("ERROR2\n"));
			ft_strncat(answer, s, i);
			if (s[i] == '\"')
				break ;
			ft_strcat(answer, "\n");
			len++;
			ft_strdel(&s);
			get_next_line(fd, &s);
			i = 0;
		}
	}
}

void	ft_read_header(header_t *h, int fd)
{
	char	*str;
	char	*s;

	h->magic = COREWAR_EXEC_MAGIC;
	get_next_line(fd, &str);
	if (ft_strncmp(str, NAME_CMD_STRING, 4) == 0)
	{
		s = ft_strtrim(str + 5);
		ft_strdel(&str);
		ft_fill_info(h->prog_name, fd, s, PROG_NAME_LENGTH);
	}
	get_next_line(fd, &str);
	if (ft_strncmp(str, COMMENT_CMD_STRING, 8) == 0)
	{
		s = ft_strtrim(str + 8);
		ft_strdel(&str);
		ft_fill_info(h->comment, fd, s, COMMENT_LENGTH);
	}
	else
		exit(ft_printf("ERROR3\n"));
}

int is_label_char(char c)
{
	int i;

	i = 0;
	while (LABEL_CHARS[i])
	{
		if (LABEL_CHARS[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	analyze_opcode(t_label **head, char *line)
{
	int		i;
	int		h;	
	t_label	*label;

	i = 0;
	while (line[i] && ft_isws(line[i]))
		i++;
	h = i;
	while (is_label_char(line[i]) && line[i] != LABEL_CHAR)
		i++;
	if (line[i] == LABEL_CHAR)
	{
		label = create_label();
		label->name = ft_strsub(line, h, i-h);
		ft_lstaddendlabel(head, label);
	}	
}

void	read_instr(int fd, char *line)
{
	t_label	*head;

	head = NULL;
	while (get_next_line(fd, &line))
	{
		analyze_opcode(&head, line);
		// ft_printf("%s\n", line);
		free(line);
	}
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
	fd2 = open("mbappe.cor", O_WRONLY | O_CREAT | O_TRUNC, 0644);		
	write_magic(fd2);
	write(fd2, h->prog_name, PROG_NAME_LENGTH);
	write(fd2, h->comment, COMMENT_LENGTH);
	read_instr(fd, line);
}