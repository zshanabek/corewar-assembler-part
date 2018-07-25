#ifndef ASM_H
# define ASM_H
# include "libft/libft.h"
# include "op.h"

typedef struct			s_param
{
	int					type;
	char				*val;
	int					value;
	size_t				size;
	struct s_param		*next;
}						t_param;

typedef struct			s_label
{
	char				*name;
	struct s_label		*next;	
}						t_label;

typedef struct			s_opcode
{
	char				*name;		
	int					codage;
	char				*opcode;
	unsigned int		size;
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
void		ft_lstaddendpar(t_param **head, t_param *item);

#endif