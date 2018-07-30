/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vradchen <vradchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2018/07/30 17:09:57 by vradchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

#include "asm.h"

#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


#define MAX_ARGS_NUMBER			4
#define MAX_PLAYERS				4
#define MEM_SIZE				(4*1024)
#define IDX_MOD					(MEM_SIZE / 8)
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

#define COMMENT_CHAR			'#'
#define LABEL_CHAR				':'
#define DIRECT_CHAR				'%'
#define SEPARATOR_CHAR			','

#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING			".name"
#define COMMENT_CMD_STRING		".comment"

#define REG_NUMBER				16

#define CYCLE_TO_DIE			1536
#define CYCLE_DELTA				50
#define NBR_LIVE				21
#define MAX_CHECKS				10

/*
**
*/

typedef char	t_arg_type;

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8

/*
**
*/

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3



typedef struct		header_s
{
  unsigned int		magic;
  char				prog_name[PROG_NAME_LENGTH + 1];
  unsigned int		prog_size;
  char				comment[COMMENT_LENGTH + 1];
}					header_t;

typedef	struct	s_op
{
	char			*name;		//x имя инструкции
	int				nb_param;	// сколько параментров
	int				param[3];	// какие параметры:T_REG = 1; T_DIR = 2; T_IND = 3;  если нет аргумента = 0
	int				opcode;		//x номер инструкции
	int				cycle;		// сколько циклов работает
	char			*full_name;	// описание инструкции
	int				coding_byte;// codage octal: true false
	int				two_bytes;	// label size: 0 eto 2, 1 eto 4
}				t_op;


static t_op    op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

t_op		*search_struct();

// typedef	struct	s_param
// {
// 	unsigned int	value;		//заполняй;значения аргумента
// 	char			*label;		//заполняй;значение
// 	int				type;		//заполняй;тип аргумента:T_REG = 1; T_DIR = 2; T_IND = 3;
// 	int				size;		//длинна параметра
// 	struct s_param	*next;		
// }				t_param;

// typedef struct	s_ins
// {
// 	char			*name;		//x заполняй;имя инструкции
// 	t_param			*param;		//x заполняй;данные аргументов инструкции
// 	int				cod_oct;	//x codage octal: 0 or 1
// 	int				lab_size;	// label size: 2 or 4
// 	char			*opcode;	// имя инструкц в хексе
// 	t_label			*label;		//x заполняй;имя лэйбла
// 	unsigned int	size;		// длинна всей инструкции, по дефолту = 0
// 	unsigned int	pos;		// позиция инструкц, по дефолту = 0
// 	struct s_ins	*next;		//x
// }				t_ins;

// void			ft_hex(t_ins *instr);
// char 			*ft_arg_join(char *s1, char *s2, int arg);
// unsigned int	ft_swp_bits(unsigned int n, int size);

typedef struct		par_s
{
	char		*name;
	int			p1[3]; //какие параметры:T_REG = 1; T_DIR = 2; T_IND = 3;  если нет аргумента = 0
	int			p2[3];
	int			p3[3];
}					par_t;

static par_t info[16] = 
{
	{"live",  {2}, {0}, {0}},
	{"ld",    {2,3}, {1}, {0}},
	{"st",    {1,0,0}, {1,0,1}, {0,0,0}},
	{"add",   {1,0,0}, {1,0,0}, {1,0,0}},
	{"sub",   {1,0,0}, {1,0,0}, {1,0,0}},
	{"and",   {1,1,1}, {1,1,1}, {1,0,0}},
	{"or",	  {1,1,1}, {1,1,1}, {1,0,0}},
	{"xor",	  {1,1,1}, {1,1,1}, {1,0,0}},
	{"zjmp",  {0,1,0}, {0,0,0}, {0,0,0}},
	{"ldi",   {1,1,1}, {1,1,0}, {1,0,0}},
	{"sti",   {1,0,0}, {1,1,1}, {1,1,0}},
	{"fork",  {0,1,0}, {0,0,0}, {0,0,0}},
	{"lld",   {0,1,1}, {1,0,0}, {0,0,0}},
	{"lldi",  {1,1,1}, {1,1,0}, {1,0,0}},
	{"lfork", {0,1,0}, {0,0,0}, {0,0,0}},
	{"aff",   {1,0,0}, {0,0,0}, {0,0,0}}
};

#endif	
