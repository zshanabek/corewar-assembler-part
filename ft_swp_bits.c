/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swp_bits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vradchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 16:53:57 by vradchen          #+#    #+#             */
/*   Updated: 2018/07/27 16:53:59 by vradchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

unsigned int	ft_swp_bits(unsigned int n, int size)
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
	{
		res_char[i++] = nn[--size];
	}
	return (res_num);
}

