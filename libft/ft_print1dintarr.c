/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print1dintarr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zshanabe <zshanabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 19:03:37 by zshanabe          #+#    #+#             */
/*   Updated: 2018/08/14 16:21:10 by zshanabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print1dintarr(int *arr, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if ((len - 1) == i)
			ft_printf(1, "%d", arr[i]);
		else
			ft_printf(1, "%d ", arr[i]);
		i++;
	}
	ft_putchar('\n');
}
