#include "asm.h"

void			ft_print_l(t_opcode *instr, t_opcode *in, t_param *p, int fd2)
{
	t_opcode	*i;
	t_label		*l;

	i = instr;
	while (i)
	{
		l = i->label;
		while (l)
		{
			if (ft_strequ(l->name, p->sval))
				return (ft_count_len(i->pos - in->pos, p, fd2));
			l = l->next;
		}
		i = i->next;
	}
}

void			ft_param(t_opcode *in, t_opcode *instruct, int fd2)
{
	t_param		*p;

	p = in->param;
	while (p)
	{
		if (p->sval != NULL)
			ft_print_l(instruct, in, p, fd2);
		else
			ft_count_len(p->ival, p, fd2);
		p = p->next;
	}
}

char			*ft_write_in2(t_opcode *in)
{
	t_param		*p;
	char		*cod;

	cod = NULL;
	p = in->param;
	while (p)
	{
		if (p->type == 0)
			break ;
		else if (p->type == 1)
			cod = ft_arg_join(cod, ft_strdup("01"), 3);
		else if (p->type == 2)
			cod = ft_arg_join(cod, ft_strdup("10"), 3);
		else if (p->type == 3)
			cod = ft_arg_join(cod, ft_strdup("11"), 3);
		p = p->next;
	}
	while (ft_strlen(cod) < 8)
		cod = ft_arg_join(cod, ft_strdup("00"), 3);
	return (cod);
}