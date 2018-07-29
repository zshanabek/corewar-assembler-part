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
    char *ret;
    char *anchor;
    int  n;

    if (s1 && s2)
    {
        anchor = s2;
        if (!(ret = (char*)malloc(sizeof(char) * ((ft_strlen(s1)
                                                   + ft_strlen(s2)) + 1))))
            return (NULL);
        n = 0;
        while (s1[n] != '\0')
        {
            ret[n] = s1[n];
            n++;
        }
        while (*s2)
            ret[n++] = *s2++;
        ret[n] = '\0';
		ft_fr(s1, s2, arg);
        free(anchor);
        return (ret);
    }
    return (NULL);
}