#include "asm.h"

t_opcode	*create_opcode(void)
{
	t_opcode *item;

	item = malloc(sizeof(t_opcode));
	item->next = NULL;
	return (item);
}

t_label		*create_label(void)
{
	t_label *item;

	item = malloc(sizeof(t_label));
	item->next = NULL;
	return (item);
}

void	ft_lstaddendopcode(t_opcode **head, t_opcode *item)
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

void	ft_lstaddendarg(t_arg **head, t_arg *item)
{
	t_arg	*current;

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
