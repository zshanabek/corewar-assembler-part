/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zshanabe <zshanabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 11:09:52 by vradchen          #+#    #+#             */
/*   Updated: 2018/09/10 18:29:15 by zshanabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op	*search_struct(char *name)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (ft_strequ(g_op[i].name, name))
			return (&g_op[i]);
		i++;
	}
	return (0);
}

int		is_label_char(char c)
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

int		is_valid_label(char *str)
{
	int i;
	int flag;

	flag = 0;
	i = 0;
	while (str[i])
	{
		if (is_label_char(str[i]))
			flag = 1;
		if (flag == 0)
			return (0);
		flag = 0;
		i++;
	}
	return (1);
}

int		is_digital(char *line)
{
	int i;

	i = 0;
	if (line == NULL)
		return (0);
	if (line[i] == '-' || ft_isdigit(line[i]))
	{
		i++;
		while (line[i])
		{
			if (!ft_isdigit(line[i]))
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

void	clear_comment(char *line)
{
	while (*line && (*line != ';' && *line != COMMENT_CHAR))
		line++;
	if (*line != '\0')
		ft_bzero(line, ft_strlen(line));
}
