#ifndef ASM_H
# define ASM_H
# include "libft/libft.h"
# include "op.h"

typedef struct s_param	t_param;
typedef struct s_label	t_label;
typedef struct s_opcode	t_opcode;

struct				s_param
{
	int				type;
	int				size;
	int				ival;
	char			*sval;
	t_param			*next;
};

struct				s_label
{
	char			*name;
	t_label			*next;
};

struct				s_opcode
{
	int 			n;
	int				codage;
	int				nb_param;
	int				lab_size;
	long			opcode;
	char			*name;
	unsigned int	pos;
	unsigned int	size;
	t_param			*param;
	t_label			*label;
	t_opcode		*next;
};

t_label				*create_label(void);
t_opcode			*create_opcode(int n);
t_param				*create_param(void);
t_op				*search_struct();
void				ft_lstaddendlabel(t_label **head, t_label *item);
void				ft_lstaddendopcode(t_opcode **head, t_opcode *item);
void				ft_lstaddendpar(t_param **head, t_param *item);
void				iter_opcode(t_opcode *ohead, void (*f)(t_opcode *elem));
void				iter_label(t_label *lhead, void (*f)(t_label *elem));
void				iter_param(t_param *head, void (*f)(t_param *elem));
void				print_label(t_label *label);
void				print_opcode(t_opcode *opcode);
void				print_param(t_param *param);
void				read_instr(int fd, int *n, t_opcode **ohead);
void				show_error(int type, int n, int a, char *str);
void				clear_comment(char *line);
void				get_i_h(int *i, int *h, char *line);
void				get_params(t_opcode *opcode, char **arr, int i);
void				is_valid_param(t_op *elem, t_param *cur, char *name);
char				**get_params_array(int i, int n, char *line);
int					is_digital(char *line);
int					is_valid_label(char *str);
int					count_commas(char *str);
int					detect_blank_line(int fd1);

void			ft_read_header(header_t *h, int *n, int fd);
int				ft_gnl(int fd, char **s);
void			ft_h(t_opcode *instr, int n);
char 			*ft_arg_join(char *s1, char *s2, int arg);
unsigned int	ft_swp_bits(int n, int size);
void			ft_write_in(t_opcode *instruct, int fd2);
char			*ft_w(t_opcode *in);
void			ft_param(t_opcode *in, t_opcode *instruct, int fd2);
void			ft_print_l(t_opcode *instr, t_opcode *in, t_param *p, int fd2);
void			ft_count_len(long value, t_param *param, int fd2);
long			ft_bin_to(char *bin);
void 			iter_opcode2(t_opcode *ohead, void (*f)(t_opcode *elem,
														t_opcode *h));
int				ft_atoi_base(const char *str, int str_base);
int 			ft_check_ac(int ac, char **av, char **name);
void			ft_bot_size(int fd2, t_opcode *ohead);
int 			ft_ohead_size(t_opcode *ohead);
void			ft_print_flag(t_opcode *in, t_opcode *ohead);
char			*ft_name(char *av);
void			ft_pr_param1(t_param *p);
void			ft_pr_param2(t_param *p, t_opcode *in, t_opcode *ohead);
void			ft_pr_param3(t_param *p, t_opcode *in, t_opcode *ohead);
char 			*ft_console(int v);
int				ft_print_l2(t_opcode *instr, t_opcode *in, t_param *p);

#endif
