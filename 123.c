#include "asm.h"
#include "op.h"

int	ft_bin_to(char *bin)
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
	//str = ft_itoa_base(x, 16);
	//return (str);
	return (x);
}

void		ft_count_len(long long int value, int size)// свапаем бит и печатаем
{
	char				*s;
	char				*ret;
	int					i;
	char				*ret2;
	unsigned int		x;
	int					fd2;

	fd2 = open("123.cor", O_WRONLY | O_CREAT | O_TRUNC, 0644);	
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
	//	s = ft_itoa_base(value, 16);
	x = ft_swp_bits(x, size);
	ft_strdel(&s);
	write(fd2, &x, size);
	//return (ret);
}

int main()
{
	//char *s = "01101000";
	//ft_printf("s %s\n", ft_bin_to_hex(s));
	ft_count_len(15, 2);
}

