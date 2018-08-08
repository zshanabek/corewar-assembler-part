/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zshanabe <zshanabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 17:28:37 by vradchen          #+#    #+#             */
/*   Updated: 2018/08/07 17:23:32 by zshanabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			ft_line_end(char *s, int i, char *str)
{
	ft_strdel(&str);
	clear_comment(s + i);
	while (s[i])
	{
		if (!ft_isws(s[i]))
			exit(ft_printf("Bad name or comment\n"));
		i++;
	}
	return (ft_strdel(&s));
}

static int		ft_f(int fd, int max, char *answer, char *str)
{
	int				i;
	int				len;
	char			*s;
	int 			gnl;

	gnl = 0;
	i = -1;
	len = -1;
	if (str[i + 1] != '\"')
		exit(ft_printf("There is no \"\n"));
	s = ft_strdup(str + 1);
	while (len++ < max)
	{
		if (s[++i] == '\0' || s[i] == '\"')
		{
			ft_strncat(answer, s, i);
			if (s[i++] == '\"')
			{
				ft_line_end(s, i, str);
				return (gnl);
			}
			ft_strcat(answer, "\n");
			gnl++;
			if (ft_gnl(fd, &s) < 1)
				exit(ft_printf("No second \"\n"));
			i = -1;
		}
	}
	if (max == 128)
		exit(ft_printf("Champion name too long (Max length 128)\n"));
	exit(ft_printf("Champion comment too long (Max length 2048)\n"));
}

char			*ft_white(char *s)
{
	int		i;
	char	*s2;

	i = 0;
	while (ft_isws(s[i]))
		i++;
	if (s[i] == '\0' || s[i] == '#' || s[i] == ';')
		return (0);
	s2 = ft_strdup(s + i);
	return (s2);
}

void			ft_read_header(header_t *h, int *n, int fd)
{
	char			*s;
	int				x;
	char			*s2;

	x = 0;
	s = NULL;
	h->magic = COREWAR_EXEC_MAGIC;
	while (ft_gnl(fd, &s) > -1)
	{
		(*n)++;
		s2 = ft_white(s);
		if (s2 == NULL || ft_strequ(s2, ""))
			continue ;
		else if (!(*h->p) && ft_strncmp(s2, NAME_CMD_STRING, 4) == 0 && ++x > 0)
			*n += ft_f(fd, PROG_NAME_LENGTH, h->p, ft_strtrim(s2 + 5));
		else if (!(*h->c) && ft_strncmp(s2, COM_CMD_STRING, 8) == 0 && ++x > 0)
			*n += ft_f(fd, COMMENT_LENGTH, h->c, ft_strtrim(s2 + 8));
		else
			exit(ft_printf("No name or header.\n"));
		if (x == 2)
			return (ft_strdel(&s));
	}
	exit(ft_printf("No name or header.\n"));
}
