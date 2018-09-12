/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zshanabe <zshanabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 23:55:21 by zshanabe          #+#    #+#             */
/*   Updated: 2018/08/15 15:50:51 by zshanabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_flag(char c)
{
	if (c == '-' || c == '0' || c == '+' || c == ' ' || c == '#')
		return (1);
	return (0);
}

int		is_modifier(char c)
{
	if (c == 'h' || c == 'l' || c == 'z' || c == 'j')
		return (1);
	return (0);
}

int		is_specifier(char c)
{
	if (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D' || c == 'i' ||
		c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == 'x' || c == 'X' ||
		c == 'c' || c == 'C')
		return (1);
	return (0);
}

void	count_return_value(t_item *form, int is_zero, int len)
{
	if (form->zer > 0 && form->spec != 'S')
		form->count += form->zer;
	if (form->pad > 0)
		form->count += form->pad;
	if (is_zero == 0 || form->zer != 0)
		form->count += len;
	if (form->hash)
	{
		if (form->spec == 'o' || form->spec == 'O')
			(form->count)++;
		else if (form->spec == 'x' || form->spec == 'X' || form->spec == 'p')
			(form->count) += 2;
	}
}

void	ft_format(const char *f, int fd, int *i, int *count)
{
	if (f[*i] == '{' && ft_isalpha(f[*i + 1]))
		*i = identify_color(f, fd, *i);
	else if (f[*i] != '%' && ft_putchar_fd(f[*i], fd))
		(*count)++;
}
