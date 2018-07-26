#include "asm.h"

void	print_label(t_label *label)
{
	ft_printf("   %s\n", label->name);
}

void	print_param(t_param *param)
{
	if (param->sval != NULL)
		ft_printf("   value: %s\n", param->sval);
	if (param->ival != -1)
		ft_printf("   value: %d\n", param->ival);
	ft_printf("   type: %d\n", param->type);
	if (param->next != NULL)
		ft_printf("----------------\n");
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

void 	iter_param(t_param *head, void (*f)(t_param *elem))
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

void	print_opcode(t_opcode *opcode)
{
	ft_printf("%s\n", opcode->name);
	if (opcode->label != NULL)
	{
		ft_printf("labels:\n");
		iter_label(opcode->label, print_label);
	}
	if (opcode->param != NULL)
	{
		ft_printf("params:\n");
		iter_param(opcode->param, print_param);
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

void	show_error()
{
	ft_printf("ERROR\n");
	exit(1);
}