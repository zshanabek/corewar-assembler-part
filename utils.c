/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zshanabe <zshanabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 21:41:18 by zshanabe          #+#    #+#             */
/*   Updated: 2018/08/11 21:41:47 by zshanabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_opcode	*create_opcode(int n)
{
	t_opcode *item;

	item = malloc(sizeof(t_opcode));
	item->n = n;
	item->name = NULL;
	item->codage = -1;
	item->nb_param = 0;
	item->opcode = -1;
	item->lab_size = 0;
	item->size = 0;
	item->pos = 0;
	item->param = NULL;
	item->label = NULL;
	item->next = NULL;
	return (item);
}

t_label		*create_label(void)
{
	t_label *item;

	item = malloc(sizeof(t_label));
	item->name = NULL;
	item->next = NULL;
	return (item);
}

t_param		*create_param(void)
{
	t_param *item;

	item = malloc(sizeof(t_param));
	item->ival = 0;
	item->type = 0;
	item->sval = NULL;
	item->next = NULL;
	return (item);
}

void		ft_lstaddendopcode(t_opcode **head, t_opcode *item)
{
	t_opcode	*current;

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

void		ft_lstaddendlabel(t_label **head, t_label *item)
{
	t_label	*current;

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
