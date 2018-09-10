/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zshanabe <zshanabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 20:27:58 by zshanabe          #+#    #+#             */
/*   Updated: 2018/08/11 20:28:00 by zshanabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				count_commas(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == SEPARATOR_CHAR)
			count++;
		i++;
	}
	return (count);
}

int				detect_blank_line(int fd)
{
	int		offset;
	char	c;
	char	*line;

	offset = lseek(fd, 0, SEEK_END);
	lseek(fd, -1, SEEK_CUR);
	read(fd, &c, 1);
	if (c == '\n')
		return (1);
	while (offset > 0 && c != '\n')
	{
		read(fd, &c, 1);
		lseek(fd, -2, SEEK_CUR);
		offset--;
	}
	lseek(fd, 2, SEEK_CUR);
	get_next_line(fd, &line);
	clear_comment(line);
	if (ft_isempty(line))
		return (1);
	ft_strdel(&line);
	return (0);
}

int				ft_gnl(int fd, char **s)
{
	int i;

	ft_strdel(s);
	i = get_next_line(fd, s);
	return (i);
}

unsigned int	ft_swp_bits(int n, int size)
{
	unsigned char	*nn;
	unsigned char	*res_char;
	unsigned int	res_num;
	int				i;

	if (size == 1)
		return (n);
	nn = (unsigned char *)&n;
	res_char = (unsigned char *)&res_num;
	i = 0;
	while (size > 0)
		res_char[i++] = nn[--size];
	return (res_num);
}
