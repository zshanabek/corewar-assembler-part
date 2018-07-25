#include "asm.h"

void	print_opcode(t_opcode *opcode)
{
	ft_printf("%s\n", opcode->name);
}

void	print_label(t_label *label)
{
	ft_printf("%s\n", label->name);
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