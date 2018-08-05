/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vradchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 17:32:21 by vradchen          #+#    #+#             */
/*   Updated: 2018/08/03 17:32:22 by vradchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				ft_bin_to(char *bin)
{
	int		i;
	int		x;
	int		power;

	power = 1;
	x = 0;
	i = 7;
	while (i > -1)
	{
		x += (bin[i] - 48) * power;
		i--;
		power *= 2;
	}
	ft_strdel(&bin);
	return (x);
}

unsigned int	ft_count_len2(char *ret, int i)
{
	unsigned int	x;

	while (i > -1)
	{
		if (ret[i] == '0')
		{
			ret[i] = '1';
			break ;
		}
		if (i == 0)
		{
			ret = ft_arg_join(ft_strdup("1"), ret, 3);
			break ;
		}
		i--;
	}
	x = ft_bin_to(ret);
	return (x);
}

void			ft_count_len(long value, t_param *param, int fd2)
{
	char				*ret;
	int					i;
	unsigned int		x;

	if (value < 0)
	{
		value = -value;
		ret = ft_itoa_base(value, 2);
		i = ft_strlen(ret) - 1;
		while (i > -1)
		{
			if (ret[i] == '0')
				ret[i] = '1';
			else
				ret[i] = '0';
			i--;
		}
		i = ft_strlen(ret) - 1;
		x = ft_count_len2(ret, i);
	}
	else
		x = value;
	x = ft_swp_bits(x, param->size);
	write(fd2, &x, param->size);
}

void			ft_write_in(t_opcode *instruct, int fd2)
{
	t_opcode	*in;
	long		x;

	in = instruct;
	if (in->opcode == -1)
		return ;
	while (in)
	{
		write(fd2, &in->opcode, 1);
		if (in->codage == 1)
		{
			x = ft_bin_to(ft_write_in2(in));
			write(fd2, &x, 1);
		}
		ft_param(in, instruct, fd2);
		in = in->next;
	}
}
