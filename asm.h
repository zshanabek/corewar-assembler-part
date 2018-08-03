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
	unsigned int		pos;	// позиция инструкц, по дефолту = 0
	int					lab_size;
	int 				nb_param;
	char				*name;		//x заполняй;имя инструкции
	long				opcode;		// имя инструкц в long
	t_param				*param;		//x заполняй;данные аргументов инструкции
	t_label				*label;		//x заполняй;имя лэйбла
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
void		print_param(t_param *param);
void		iter_param(t_param *head, void (*f)(t_param *elem));
void		read_instr(int fd, char *line, t_opcode **ohead);
t_param		*create_param(void);
void		ft_lstaddendpar(t_param **head, t_param *item);
void		show_error();
t_op		*search_struct();
int			opcode_bar_ma(char *name);
void		clear_comment(char *line);
int			is_valid_param(t_opcode *to_find);
int			is_digital(char *line);
int			is_valid_label(char *str);
char		**get_params_array(t_opcode *opcode, int i, char *line);
void		get_params(t_opcode *opcode, char **arr);
int			count_commas(char *str);
void		ft_inslstdel(t_opcode **head);
int			detect_blank_line(int fd1);

void			ft_read_header(header_t *h, int fd);
int				ft_gnl(int fd, char **s);
void			ft_hex(t_opcode *instr);
char 			*ft_arg_join(char *s1, char *s2, int arg);
unsigned int	ft_swp_bits(unsigned int n, int size);
void			ft_write_in(t_opcode *instruct, int fd2);
char			*ft_write_in2(t_opcode *in);
void			ft_param(t_opcode *in, t_opcode *instruct, int fd2);
void			ft_print_l(t_opcode *instr, t_opcode *in, t_param *p, int fd2);
void			ft_count_len(long value, t_param *param, int fd2);
#endif