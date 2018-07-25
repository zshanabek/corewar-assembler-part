#include "asm.h"
#include "op.h"

char *ft_arrg_join(char *s1, char *s2)
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
        free(s1);
        free(anchor);
        return (ret);
    }
    return (NULL);
}