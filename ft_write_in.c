#include "asm.h"
#include "op.h"

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

void		ft_count_len(long long int value, t_param *param, int fd2)// свапаем бит и печатаем
{
	char				*ret;
	int					i;
	char				*ret2;
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
				ret = ft_arrg_join("1", ret); // LEAK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				break ;
			}
			i--;
		}
		//s = ft_bin_to(ret);
		x = ft_bin_to(ret);
		ft_strdel(&ret);
	}
	else
		x = value;
	x = ft_swp_bits(x, param->size);
	write(fd2, &x, param->size);
	//return (ret);
}

void		ft_print_label(t_ins *instruct, t_ins *in, t_param *p, int fd2)
{
	t_ins *i;
	t_label	*l;
	char *s;

	i = instruct;
	while (i)
	{
		l = i->label;
		while (l)
		{
			if (ft_strequ(l->name, p->label))
				return (ft_count_len(i->pos - in->pos, p, fd2));
			l = l->next;
		}
	}
	//return (0);
}

void	*ft_param(t_ins *in, t_ins *instruct, int fd2)
{
	t_ins	*i;
	t_label	*l;
	t_param	*p;
	char	*s;

	p = in->param;
	while (p)
	{
		if (p->label != NULL)
			ft_print_label(instruct, in, p, fd2);
		else
			ft_count_len(p->value, p, fd2);
			//s = ft_arrg_join(s, ft_count_len(p->value, p, fd2));
		p = p->next;
	}
	return (s);
}


void	ft_write_in(t_ins *instruct, int fd2)
{
	t_label	*l;
	t_ins	*in;
	t_param	*p;
	char	*cod;
	int		x;

	in = instruct;
	while (in)
	{
		write(fd2, &in->opcode, 1);//str = ft_arrg_join(str, in->opcode);// печатаем опкод
		if (in->cod_oct == 1)
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
			x = ft_bin_to(cod);
			write(fd2, &x, 1);//печатаем кодировку параметров
		}
		ft_param(in, instruct, fd2);
		in = in->next;
	}
}