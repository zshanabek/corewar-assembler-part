#include "asm.h"

t_opcode	*create_opcode(void)
{
	t_opcode *item;

	item = malloc(sizeof(t_opcode));
	item->name = NULL;
	item->codage = -1;
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
	item->ival = -1;
	item->type = 0;	
	item->sval = NULL;	
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
