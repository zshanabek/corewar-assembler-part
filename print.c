#include "asm.h"

void	print_label(t_label *label)
{
	ft_printf("%s\n", label->name);
}

void 	iter_label(t_label *lhead, void (*f)(t_label *elem))
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

void	print_opcode(t_opcode *opcode)
{
	ft_printf("%s\n", opcode->name);
	if (opcode->label != NULL)
	{
		ft_printf("labels: ");
		iter_label(opcode->label, print_label);
	}
}

void 	iter_opcode(t_opcode *ohead, void (*f)(t_opcode *elem))
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
