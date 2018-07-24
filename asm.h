#ifndef ASM_H
# define ASM_H
# include "libft/libft.h"
# include "op.h"

typedef struct			s_label
{
	char				*name;
	struct s_label		*next;
}						t_label;

typedef struct			s_arg
{
	int					type_arg;
	char				*val;
	int					value;
	size_t				arg_size;
	struct s_arg		*next;
}						t_arg;

typedef struct			s_opcode
{
	char				*name;
	int					op;
	int					type;
	int					codage;
	int					par;
	t_label				*label;
	t_arg				*args;
	struct s_opcode		*next;
	size_t				size;
}						t_opcode;

t_label		*create_label(void);
void		ft_lstaddendlabel(t_label **head, t_label *item);

#endif