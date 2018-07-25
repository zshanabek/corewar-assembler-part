#include "asm.h"
#include "op.h"

t_op    op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

int ft_param_len(t_ins *in, t_param *p)
{
	if (p->type == 0)
		return (0);
	else if (p->type == 1)
		return (1);
	else if	(p->type == 2 && in->codage == 4)
		return (4);
	else //if (in->op.param[i] == 3 ||)
		return (2);
}

void	ft_hex(t_ins *instr)
{
	int		len;
	t_ins	*in;
	t_param	*p;
	int		i;

	len = 1;
	while (in)
	{
		in->pos = len;
		i = 0;
		while (i < 17)
		{
			if (ft_strequ(in->name, op_tab[i].name))
			{
				in->opcode = ft_itoa_base(op_tab[i].opcode, 16);
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
			// if (p->type == 0)
			// 	break;
			// else if (p->type == 1)
			// 	in->size++;
			// else if	(p->type == 2 && in->codage == 4)
			// 	in->size += 4;
			// else //if (in->op.param[i] == 3 ||)
			// 	in->size += 2;
			in->size += p->size;
			p = p->next;
		}
		len += in->size;
		in = in->next;
	}
}