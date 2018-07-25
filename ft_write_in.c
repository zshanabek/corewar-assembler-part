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

char	*ft_count_len(long long int value, t_param *param)// перевести параметр в хекс, подогнать под размер и вернуть
{
	char				*s;
	char				*ret;
	int					i;
	char				*ret2;

	if (value < 0)
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
		s = ft_bin_to_hex(ret);
		ft_strdel(&ret);
	}
	else
		s = ft_itoa_base(value, 16);
	while(ft_strlen(s) != (param->size * 2))
	{
		ft_strdel(&ret);
		ret = ft_arrg_join("0", s);
	}
	ft_strdel(s);
	return (ret);
}

char	*ft_print_label(t_ins *instruct, t_ins *in, t_param *p)
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
			{
				//s = ft_arrg_join(s, ft_count_len(i->pos - in->pos, p));//ft_itoa_base(i->pos - in->pos, 16));
				return (ft_count_len(i->pos - in->pos, p));
				//break ;
			}
			l = l->next;
		}
	}
	return (0);
}

char	*ft_param(t_ins *in, t_ins *instruct)
{
	t_ins	*i;
	t_label	*l;
	t_param	*p;
	char	*s;

	p = in->param;
	while (p)
	{
		if (p->label != NULL)
		{
			s = ft_arrg_join(s, ft_print_label(instruct, in, p));
			// i = instruct;
			// while (i)
			// {
			// 	l = i->label;
			// 	while (l)
			// 	{
			// 		if (ft_strequ(l->name, p->label))
			// 		{
			// 			s = ft_arrg_join(s, ft_count_len(i->pos - in->pos, p));//ft_itoa_base(i->pos - in->pos, 16));
			// 			break ;
			// 		}
			// 		l = l->next;
			// 	}
			// }
		}
		else
			s = ft_arrg_join(s, ft_count_len(p->value, p));
		p = p->next;
	}
	return (s);
}


void	ft_write_in(t_ins *instruct)
{
	char	*str;
	t_label	*l;
	t_ins	*in;
	t_param	*p;
	char	*cod;

	str = NULL;
	while (in)
	{
		str = ft_arrg_join(str, in->opcode);
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
			str = ft_arrg_join(str, ft_bin_to_hex(cod));
		}
		str = ft_arrg_join(str, ft_param(in, instruct)); //вот вызов
		//ft_to_file();// в str записана вся инструкция, можно записывать в файл
		in = in->next;
	}
}