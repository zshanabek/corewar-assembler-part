#include "asm.h"

void	print_label(t_label *label)
{
	ft_printf("{blue}   %s{eoc}\n", label->name);
}

void	print_param(t_param *param)
{
	if (param->sval != NULL)
		ft_printf("   sval: %s\n", param->sval);
	ft_printf("   ival: {yellow}%d{eoc}\n", param->ival);
	ft_printf("   type: %d\n", param->type);
	if (param->next != NULL)
		ft_printf("--------------\n");
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
	ft_printf("name: {magenta}%s{eoc}\n", opcode->name);
	// ft_printf("cod:  %d\n", opcode->codage);
	// ft_printf("npar:  %d\n", opcode->nb_param);
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
	ft_printf("////////////////\n");
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

char	**get_array()
{
	char	**mrr;

	mrr = malloc(sizeof(char *) * 4);
	mrr[0] = ft_strdup("reg");
	mrr[1] = ft_strdup("direct");
	mrr[2] = ft_strdup("indirect");
	mrr[3] = NULL;
	return (mrr);
}

void	show_error(int type, int n, int a, char *str)
{
	char	**mrr;
	
	if (type == 0)
		printf("Syntax error at token [%03d] INSTRUCTION %s\n", n, str);
	else if (type == 1)
		ft_printf("Syntax error at token [%03d] SEPARATOR \",\"\n", n);
	else if (type == 2)
		ft_printf("Syntax error at token [%03d] ENDLINE\n", n);
	else if (type == 3)
		ft_printf("Invalid instruction at token [%03d] INSTRUCTION \"%s\"\n", n, str);
	else if (type == 4)
	{
		mrr = get_array();
		ft_printf("Invalid parameter %d type %s for instruction %s\n", n, mrr[a], str);
		ft_del2darr(mrr);	
	}
	else if (type == 5)
		ft_printf("Invalid parameter count for instruction \"%s\"\n", str);
	else if (type == 6)
		ft_printf("Lexical error at [%d]\n", n);
	else if (type == 7)
		ft_printf("Syntax error at token [%03d] END \"(null)\"\n", n);
	exit(1);
}
