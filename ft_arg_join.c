#include "asm.h"
#include "op.h"

static	void	ft_fr(char *s1, char *s2, int arg)
{
	if (arg == 1)
		ft_strdel(&s1);
	else if (arg == 2)
		ft_strdel(&s2);
	else if (arg == 3)
	{
		ft_strdel(&s1);
		ft_strdel(&s2);
	}
}

char			*ft_arg_join(char *s1, char *s2, int arg)
{
    char	*ret;
    int		n;
	int		i;
	
	if (s1 == NULL && s2 != NULL)
	{
		if (!(ret = (char*)malloc(sizeof(char) * (ft_strlen(s2) + 1))))
            return (NULL);
		n = -1;
		while (s2[++n])
            ret[n] = s2[n];
	}
	else if (s2 == NULL && s1 != NULL)
	{
		if (!(ret = (char*)malloc(sizeof(char) * (ft_strlen(s1) + 1))))
            return (NULL);
		n = -1;
		while (s1[++n])
            ret[n] = s1[n];
	}
    else if (s1 && s2)
    {
        if (!(ret = (char*)malloc(sizeof(char) * ((ft_strlen(s1)
                                                   + ft_strlen(s2)) + 1))))
            return (NULL);
        n = -1;
        while (s1[++n])
            ret[n] = s1[n];
		i = -1;
        while (s2[++i])
            ret[n++] = s2[i];
        ret[n] = '\0';
    }
	else
    	return (NULL);
	ft_fr(s1, s2, arg);
	return (ret);

}