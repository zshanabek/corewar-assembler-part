/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zshanabe <zshanabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 21:40:39 by zshanabe          #+#    #+#             */
/*   Updated: 2018/08/11 21:43:14 by zshanabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	iter_label(t_label *lhead, void (*f)(t_label *elem))
{
	t_label *cur;

	if (!lhead)
		return ;
	cur = lhead;
	while (cur != NULL)
	{
		f(cur);
		cur = cur->next;
	}
}

void	iter_param(t_param *head, void (*f)(t_param *elem))
{
	t_param *cur;

	if (!head)
		return ;
	cur = head;
	while (cur != NULL)
	{
		f(cur);
		cur = cur->next;
	}
}

void	iter_opcode2(t_opcode *ohead, void (*f)(t_opcode *elem, t_opcode *h))
{
	t_opcode *cur;

	if (!ohead)
		return ;
	cur = ohead;
	while (cur != NULL)
	{
		f(cur, ohead);
		cur = cur->next;
	}
}

void	iter_opcode(t_opcode *ohead, void (*f)(t_opcode *elem))
{
	t_opcode *cur;

	if (!ohead)
		return ;
	cur = ohead;
	while (cur != NULL)
	{
		f(cur);
		cur = cur->next;
	}
}

void	ft_lstaddendpar(t_param **head, t_param *item)
{
	t_param	*current;

	if (*head == NULL)
	{
		*head = item;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = item;
}
