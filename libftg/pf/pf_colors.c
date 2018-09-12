/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zshanabe <zshanabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 23:04:18 by zshanabe          #+#    #+#             */
/*   Updated: 2018/08/14 18:08:05 by zshanabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		put_color(char *color, int fd)
{
	if (ft_strequ(color, "red"))
		ft_putstr_fd("\x1b[31m", fd);
	else if (ft_strequ(color, "green"))
		ft_putstr_fd("\x1b[32m", fd);
	else if (ft_strequ(color, "yellow"))
		ft_putstr_fd("\x1b[33m", fd);
	else if (ft_strequ(color, "blue"))
		ft_putstr_fd("\x1b[34m", fd);
	else if (ft_strequ(color, "magenta"))
		ft_putstr_fd("\x1b[35m", fd);
	else if (ft_strequ(color, "cyan"))
		ft_putstr_fd("\x1b[36m", fd);
	else if (ft_strequ(color, "eoc"))
		ft_putstr_fd("\x1b[0m", fd);
	else
		return (0);
	return (1);
}

int				identify_color(const char *s, int fd, int i)
{
	int		len;
	int		k;
	char	*color;

	len = 0;
	k = i;
	while (s[i] && s[i] != '}')
	{
		i++;
		len++;
	}
	color = ft_strsub(s, k + 1, len - 1);
	if (put_color(color, fd) == 0)
	{
		ft_putchar_fd('{', fd);
		i = k;
	}
	free(color);
	return (i);
}
