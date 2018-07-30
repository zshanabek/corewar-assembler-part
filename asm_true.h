#ifndef ASM_H
# define ASM_H
# include "libft/libft.h"
# include "op.h"

typedef struct			s_param
{
	int					ival;	//заполняй;значения аргумента
	char				*sval;	//заполняй;значение char
	int					type;	//заполняй;тип аргумента:T_REG = 1; T_DIR = 2; T_IND = 3;
	int					size;	
	struct s_param		*next;
}						t_param;

typedef struct			s_label
{
	char				*name;
	struct s_label		*next;	
}						t_label;

typedef struct			s_opcode
{
	int					codage;	// codage octal: 0 or 1
	unsigned int		size;	// длинна всей инструкции, по дефолту = 0
	unsigned int		pos;		// позиция инструкц, по дефолту = 0
	int					lab_size;
	char				*name;	//x заполняй;имя инструкции
	char				*opcode;// имя инструкц в хексе
	t_param				*param;	//x заполняй;данные аргументов инструкции
	t_label				*label;	//x заполняй;имя лэйбла
	struct s_opcode		*next;
}						t_opcode;

t_label		*create_label(void);
void		ft_lstaddendlabel(t_label **head, t_label *item);
t_opcode	*create_opcode(void);
void		ft_lstaddendopcode(t_opcode **head, t_opcode *item);
void		iter_opcode(t_opcode *ohead, void (*f)(t_opcode *elem));
void		iter_label(t_label *lhead, void (*f)(t_label *elem));
void		print_label(t_label *label);
void		print_opcode(t_opcode *opcode);
void		read_instr(int fd, char *line, t_opcode *ohead);
t_param		*create_param(void);
void		ft_lstaddendpar(t_param **head, t_param *item);
void		show_error();

int			opcode_bar_ma(char *name);
void		clear_comment(char *line);

void			ft_hex(t_opcode *instr);
char 			*ft_arg_join(char *s1, char *s2, int arg);
unsigned int	ft_swp_bits(unsigned int n, int size);
void			ft_write_in(t_opcode *instruct, int fd2);

#endif