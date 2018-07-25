#ifndef ASM_H
# define ASM_H
# include "libft/libft.h"
# include "op.h"

typedef struct			s_param
{
	int					type_arg;
	char				*val;
	int					value;
	size_t				arg_size;
	struct s_param		*next;
}						t_param;

typedef struct	s_label
{
	char			*name;		//имя лейбла
	unsigned int	size;		//длинна всего лейбла
	struct s_label	*next;	
	unsigned int	pos;		
}					t_label;

typedef struct			s_opcode
{
	char				*name;		// имя инструкции
	int					codage;
	char				*opcode;
	unsigned int		size;		//длинна всей инструкции	
	t_param				*param;		//данные аргументов инструкции	
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

#endif