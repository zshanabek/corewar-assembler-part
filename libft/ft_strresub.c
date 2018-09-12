/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strresub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zshanabe <zshanabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 19:11:03 by zshanabe          #+#    #+#             */
/*   Updated: 2018/08/07 19:38:32 by zshanabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strresub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*temp;
	size_t	i;

	temp = (char *)s;
	if (!temp)
		return (0);
	i = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (0);
	while (temp[start] && i < len)
	{
		str[i] = temp[start];
		start++;
		i++;
	}
	str[i] = '\0';
	ft_strdel(&temp);
	return (str);
}
