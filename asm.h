#ifndef ASM_H
# define ASM_H
# include "libft/libft.h"
# include "op.h"

typedef struct		s_label
{
	char			*label;
	struct s_label 	*next;
}					t_label;


#endif