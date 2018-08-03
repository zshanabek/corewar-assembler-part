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
#define COM_CMD_STRING		".comment"

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
  char				p[PROG_NAME_LENGTH + 1];
  unsigned int		prog_size;
  char				c[COMMENT_LENGTH + 1];
}					header_t;

typedef	struct	s_op
{
	char			*name;		//x имя инструкции
	int				nb_param;	// сколько параментров
	int				param[3][3];
	int				opcode;		//x номер инструкции
	int				coding_byte;// codage octal: true false
	int				two_bytes;	// label size: 0 eto 2, 1 eto 4
}				t_op;

static t_op    op_tab[17] =
{
	{"live",  1, {{2}, {}, {}},           1,  0, 0},
	{"ld",	  2, {{2,3}, {1}, {}},        2,  1, 0},
	{"st",    2, {{1}, {1,3}, {}},        3,  1, 0},
	{"add",   3, {{1}, {1}, {1}},         4,  1, 0},
	{"sub",   3, {{1}, {1}, {1}},         5,  1, 0},
	{"and",   3, {{1,2,3}, {1,2,3}, {1}}, 6,  1, 0},
	{"or",    3, {{1,2,3}, {1,2,3}, {1}}, 7,  1, 0},
	{"xor",   3, {{1,2,3}, {1,2,3}, {1}}, 8,  1, 0},
	{"zjmp",  1, {{2}, {}, {}},           9,  0, 1},
	{"ldi",   3, {{1,2,3}, {1,2}, {1}},   10, 1, 1},
	{"sti",   3, {{1}, {1,2,3}, {1,2}},   11, 1, 1},
	{"fork",  1, {{2}, {}, {}},           12, 0, 1},
	{"lld",   2, {{2,3}, {1}, {}},        13, 1, 0},
	{"lldi",  3, {{1,2,3}, {1,2}, {1}},   14, 1, 1},
	{"lfork", 1, {{2}, {}, {}},           15, 0, 1},
	{"aff",	  1, {{1}, {}, {}},           16, 1, 0},
	{0,       0, {{}, {}, {}},            0,  0, 0}
};

#endif	
