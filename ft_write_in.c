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
			str = ft_strjoin(str, in->opcode);
			if (in->codage == 1)
			{
				p = in->param;
				while (p)
				{
					if (p->type == 0)
						break ;
					else if (p->type == 1)
						cod = ft_strjoin(cod, "01");
					else if (p->type == 2)
						cod = ft_strjoin(cod, "10");
					else if (p->type == 3)
						cod = ft_strjoin(cod, "11");
					p =p->next;
				}
				while (ft_strlen(cod) < 8)
					cod = ft_strjoin(cod, "00");
				str = ft_strjoin(str, ft_bin_to_hex(cod)); 
			}
			in = in->next;
		}
		l = l->next;
	}
}