/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zshanabe <zshanabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 15:12:45 by vradchen          #+#    #+#             */
/*   Updated: 2018/08/05 22:22:15 by zshanabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static	void	ft_fr(char *s1, char *s2, int arg)
{
	if (arg == 1)
		ft_strdel(&s1);
	else if (arg == 2)
		ft_strdel(&s2);
	else if (arg == 3)
	{
		ft_strdel(&s1);
		ft_strdel(&s2);
	}
}

static char		*ft_arg_join2(char *s1, char *s2)
{
	char	*ret;
	int		n;
	int		i;

	ret = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	n = -1;
	while (s1[++n])
		ret[n] = s1[n];
	i = -1;
	while (s2[++i])
		ret[n++] = s2[i];
	ret[n] = '\0';
	return (ret);
}

char			*ft_arg_join(char *s1, char *s2, int arg)
{
	char	*ret;

	if (s1 == NULL && s2 != NULL)
		ret = ft_strdup(s2);
	else if (s2 == NULL && s1 != NULL)
		ret = ft_strdup(s1);
	else if (s1 && s2)
		ret = ft_arg_join2(s1, s2);
	else
		return (NULL);
	ft_fr(s1, s2, arg);
	return (ret);
}
