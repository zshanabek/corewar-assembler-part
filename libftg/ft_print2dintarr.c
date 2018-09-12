/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print2dintarr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zshanabe <zshanabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 19:02:52 by zshanabe          #+#    #+#             */
/*   Updated: 2018/07/18 10:16:26 by zshanabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print2dintarr(int **matrix, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		ft_print1dintarr(matrix[i], len);
		i++;
	}
}
