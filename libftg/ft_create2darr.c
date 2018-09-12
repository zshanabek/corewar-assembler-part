/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create2darr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zshanabe <zshanabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 00:23:13 by zshanabe          #+#    #+#             */
/*   Updated: 2018/06/18 00:23:14 by zshanabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_create2darr(int n, int x)
{
	int		i;
	char	**arr;

	i = 0;
	arr = malloc(sizeof(char *) * (n + 1));
	while (i < n)
	{
		arr[i] = ft_strnew(x);
		i++;
	}
	arr[i] = 0;
	return (arr);
}
