#include "asm.h"
#include "op.h"

char	*ft_bin_to_hex(char *bin)
{
	int		i;
	int		x;
	char	*str;
	int		power;

	power = 1;
	x = 0;
	i = 7;
	while (i > -1)
	{
		x += (bin[i] -  48) * power;
		i--;
		power *= 2;
	}
	str = ft_itoa_base(x, 16);
	return (str);
}

char	*ft_param(t_param *param, t_label *l, t_label *label_all)
{
	t_param	*p;
	t_label	*l_all;
	char	*s;

	p = param;
	while (p)
	{
		if (p->label != NULL)
		{
			l_all = label_all;
			while (l_all)
			{
				if (ft_strequ(l_all->name, p->label))
				{
					s = ft_arrg_join(s, ft_itoa_base(l_all->pos - l->pos, 16));
					break ;
				}
				l_all = l_all->next;
			}
		}
		else
		{
			s = ft_arrg_join(s, ft_itoa_base(p->value , 16));
		}
		p = p->next;
	}
}


void	ft_write_in(t_label *label)
{
	char	*str;
	t_label	*l;
	t_ins	*in;
	t_param	*p;
	char	*cod;

	str = NULL;
	l = label;
	while (l)
	{
		in = l->instr;
		while (in)
		{
			str = ft_arrg_join(str, in->opcode);
			if (in->codage == 1)
			{
				p = in->param;
				while (p)
				{
					if (p->type == 0)
						break ;
					else if (p->type == 1)
						cod = ft_arrg_join(cod, "01");
					else if (p->type == 2)
						cod = ft_arrg_join(cod, "10");
					else if (p->type == 3)
						cod = ft_arrg_join(cod, "11");
					p =p->next;
				}
				while (ft_strlen(cod) < 8)
					cod = ft_arrg_join(cod, "00");
				str = ft_arrg_join(str, ft_bin_to_hex(cod));
			}
			str = ft_arrg_join(str, ft_param(in->param, l, label));
			in = in->next;
		}
		l = l->next;
	}
}