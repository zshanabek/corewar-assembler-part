/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zshanabe <zshanabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 12:01:03 by vradchen          #+#    #+#             */
/*   Updated: 2018/09/11 15:04:43 by zshanabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			ft_bot_size(int fd2, t_opcode *ohead)
{
	t_opcode		*i;
	int				bot_size;
	unsigned int	len;

	len = 0;
	if (ohead == NULL)
	{
		write(fd2, &len, 4);
		return ;
	}
	i = ohead;
	while (i->next)
		i = i->next;
	bot_size = i->pos + i->size;
	len = ft_swp_bits(bot_size, 4);
	write(fd2, &len, 4);
}

char			*ft_name(char *av)
{
	char	*n;
	int		i;

	n = ft_strdup(av);
	i = ft_strlen(n);
	while (i > -1)
	{
		if (n[i] == '.' || i == 0)
		{
			ft_strclr(n + i);
			break ;
		}
		i--;
	}
	n = ft_arg_join(n, ft_strdup(".corr"), 3);
	return (n);
}

int				ft_check_ac(int ac, char **av, char **name)
{
	char *temp;

	if (ac == 3)
	{
		if (!(ft_strequ(av[1], "-a") || ft_strequ(av[2], "-a")))
			exit(ft_printf(2, "Usage: ./asm %s\n", av[2]));
		if (ft_strequ(av[1], "-a"))
		{
			*name = av[2];
			return (2);
		}
		*name = av[1];
		return (1);
	}
	else if (ac != 2)
		exit(ft_printf(2, "Usage: ./asm %s\n", av[1]));
	*name = av[1];
	temp = *name;
	if (temp[ft_strlen(temp) - 1] != 's')
		exit(ft_printf(2, "Wrong file without .s extension\n"));
	return (0);
}

int				ft_ohead_size(t_opcode *ohead)
{
	t_opcode	*h;

	h = ohead;
	while (h->next)
		h = h->next;
	return (h->size + h->pos);
}
