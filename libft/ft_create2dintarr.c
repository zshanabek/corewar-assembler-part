/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create2dintarr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zshanabe <zshanabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 17:50:21 by zshanabe          #+#    #+#             */
/*   Updated: 2018/06/27 18:15:14 by zshanabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		**ft_create2dintarr(int n, int x)
{
	int		i;
	int		**arr;

	i = 0;
	if ((arr = malloc(sizeof(int *) * n)) == NULL)
		return (NULL);
	while (i < n)
	{
		if ((arr[i] = malloc(sizeof(int) * x)) == NULL)
			return (NULL);
		i++;
	}
	arr[i] = 0;
	return (arr);
}
