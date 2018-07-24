#ifndef ASM_H
# define ASM_H
# include "libft/libft.h"
# include "op.h"

// typedef struct		s_label
// {
// 	char			*label;
// 	struct s_label 	*next;
// }					t_label;

typedef	struct 		s_arg
{
	char			*value;
	int				value;
}					t_arg;

typedef struct 		s_cmd
{
	int 			opcode;
	
}					t_cmd;

#endif