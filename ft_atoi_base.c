/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vradchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 12:46:00 by vradchen          #+#    #+#             */
/*   Updated: 2018/08/13 12:46:01 by vradchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	ft_iswhitespace(char c)
{
	if (c == '\n' || c == '\t' || c == ' ')
		return (1);
	return (0);
}

static int	ft_base(int c, int base)
{
	char	*str;
	char	*str2;
	int		i;

	i = 0;
	str = "0123456789abcdef";
	str2 = "0123456789abcdef";
	while (i < base)
	{
		if (c == str[i] || c == str2[i])
			return (i);
		i++;
	}
	return (-1);
}

int			ft_atoi_base(const char *str, int str_base)
{
	int		nb;
	int		minus;
	int		i;

	i = 0;
	nb = 0;
	minus = 0;
	while (ft_iswhitespace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minus = 1;
		i++;
	}
	while (ft_base(str[i], str_base) != -1)
	{
		nb *= str_base;
		nb += ft_base(str[i], str_base);
		i++;
	}
	if (minus)
		return (-nb);
	return (nb);
}
