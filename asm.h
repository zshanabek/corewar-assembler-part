#ifndef ASM_H
# define ASM_H
# include "libft/libft.h"
# include "op.h"

typedef struct			s_param
{
	int					type;
	int					ival;
	size_t				size;
	char				*sval;
	struct s_param		*next;
}						t_param;

typedef struct			s_label
{
	char				*name;
	struct s_label		*next;	
}						t_label;

typedef struct			s_opcode
{
	int					codage;	
	unsigned int		size;
	char				*name;
	char				*opcode;
	t_param				*param;
	t_label				*label;
	struct s_opcode		*next;
}						t_opcode;

t_label		*create_label(void);
void		ft_lstaddendlabel(t_label **head, t_label *item);
t_opcode	*create_opcode(void);
void		ft_lstaddendopcode(t_opcode **head, t_opcode *item);
void		iter_opcode(t_opcode *ohead, void (*f)(t_opcode *elem));
void		print_opcode(t_opcode *opcode);
void		read_instr(int fd, char *line);
t_param		*create_param(void);
void		ft_lstaddendpar(t_param **head, t_param *item);
void		show_error();
t_op		*search_struct();

#endif