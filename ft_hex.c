#include "asm.h"

int ft_param_len(t_opcode *in, t_param *p)
{
	if (p->type == 0)
		return (0);
	else if (p->type == 1)
		return (1);
	else if	(p->type == 2 && in->lab_size == 4)
		return (4);
	else //if (in->op.param[i] == 3 ||)
		return (2);
}

void	ft_hex(t_opcode *instr)
{
	int			len;
	t_opcode	*in;
	t_param		*p;
	int		i;

	len = 0;
	in = instr;
	while (in)
	{
		in->pos = len;
		i = 0;
		while (i < 16)
		{
			if (ft_strequ(in->name, op_tab[i].name))
			{
				in->opcode = op_tab[i].opcode;//ft_itoa_base(op_tab[i].opcode, 16);
				in->codage = op_tab[i].coding_byte;
				if (op_tab[i].two_bytes == 1)
					in->lab_size = 2;
				else
					in->lab_size = 4;
				break ;
			}
			i++;
		}
		in->size = 1; // opcode name
		if (in->codage == 1)
			in->size++;
		p = in->param;
		while (p)
		{
			p->size = ft_param_len(in, p);
			//ft_printf("n %s size_param %i \n", in->name, p->size);
			in->size += p->size;
			p = p->next;
		}
		len += in->size;
		//ft_printf("n %s size %i \n", in->name, in->size);
		//if (len > )// тут нужна проверка что размер инструкций не вышел за макс
		in = in->next;
	}
	//ft_write_in(in);
}