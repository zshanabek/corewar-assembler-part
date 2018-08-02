#include "asm.h"

int	ft_bin_to(char *bin)
{
	int		i;
	int		x;
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
	return (x);
}

void		ft_count_len(long value, t_param *param, int fd2)// свапаем бит и печатаем
{
	char				*ret;
	int					i;
	unsigned int		x;

	if (value < 0)//если число отриц то всё плохо
	{
		value = -value;
		ret = ft_itoa_base(value, 2);
		i = ft_strlen(ret) - 1;
		while (i > -1)
		{
			if (ret[i] == '0')
				ret[i] = '1';
			else
				ret[i] = '0';
			i--;
		}
		i = ft_strlen(ret) - 1;
		while (i > -1)
		{
			if (ret[i] == '0')
			{
				ret[i] = '1';
				break ;
			}
			if (i == 0)
			{
				ret = ft_arg_join(ft_strdup("1"), ret, 3);
				break ;
			}
			i--;
		}
		x = ft_bin_to(ret);
		ft_strdel(&ret);
	}
	else
		x = value;
	x = ft_swp_bits(x, param->size);
	write(fd2, &x, param->size);
}

void		ft_print_label(t_opcode *instruct, t_opcode *in, t_param *p, int fd2)
{
	t_opcode	*i;
	t_label		*l;

	i = instruct;
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

void	ft_param(t_opcode *in, t_opcode *instruct, int fd2)
{
	t_param		*p;

	p = in->param;
	while (p)
	{
		if (p->sval != NULL)
			ft_print_label(instruct, in, p, fd2);
		else
			ft_count_len(p->ival, p, fd2);
		p = p->next;
	}
}


void	ft_write_in(t_opcode *instruct, int fd2)
{
	t_opcode	*in;
	t_param		*p;
	char		*cod;
	long		x;

	cod = NULL;
	in = instruct;
	while (in)
	{
		write(fd2, &in->opcode, 1);// печатаем опкод
		if (in->codage == 1)
		{
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
				cod = ft_arg_join(cod, "00", 1);
			x = ft_bin_to(cod);
			write(fd2, &x, 1);
			ft_strdel(&cod);
		}
		ft_param(in, instruct, fd2);
		in = in->next;
	}
}