/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zshanabe <zshanabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 17:28:37 by vradchen          #+#    #+#             */
/*   Updated: 2018/08/05 22:02:39 by zshanabe         ###   ########.fr       */
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

static void		ft_f(char *answer, int fd, char *str, int max)
{
	int				i;
	int				len;
	char			*s;
	int				x;

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
				return (ft_line_end(s, i, str));
			ft_strcat(answer, "\n");
			x = ft_gnl(fd, &s);
			if (x == 0 || x == -1)
				exit(ft_printf("No second \"\n"));
			i = -1;
		}
	}
	exit(ft_printf("Too big line\n"));
}

void			ft_read_header(header_t *h, int fd)
{
	char			*s;
	int				x;

	x = 0;
	s = NULL;
	h->magic = COREWAR_EXEC_MAGIC;
	while (ft_gnl(fd, &s) > -1)
	{
		if (ft_strequ(s, ""))
			continue;
		else if (!(*h->p) && ft_strncmp(s, NAME_CMD_STRING, 4) == 0 && ++x > 0)
			ft_f(h->p, fd, ft_strtrim(s + 5), PROG_NAME_LENGTH);
		else if (!(*h->c) && ft_strncmp(s, COM_CMD_STRING, 8) == 0 && ++x > 0)
			ft_f(h->c, fd, ft_strtrim(s + 8), COMMENT_LENGTH);
		else
			exit(ft_printf("No name or header.\n"));
		if (x == 2)
			return (ft_strdel(&s));
		ft_strdel(&s);
	}
	exit(ft_printf("No name or header.\n"));
}
