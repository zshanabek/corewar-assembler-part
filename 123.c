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

int main()
{
	char *s = "10111001";
	ft_printf("s %s\n", ft_bin_to_hex(s));
}