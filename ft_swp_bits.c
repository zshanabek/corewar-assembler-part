/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swp_bits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vradchen <vradchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 16:53:57 by vradchen          #+#    #+#             */
/*   Updated: 2018/08/02 16:57:54 by vradchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
	//ft_printf("n1 %lld\n", n);
	while (size > 0)
		res_char[i++] = nn[--size];
	//ft_printf("n2 %lld\n", res_num);
	return (res_num);
}

