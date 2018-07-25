/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vradchen <vradchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2018/07/25 16:07:43 by vradchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/
#ifndef OP_H
#define OP_H

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
	char			*name;		// имя инструкции
	int				nb_param;	// сколько параментров
	int				param[3];	// какие параметры:T_REG = 1; T_DIR = 2; T_IND = 3;  если нет аргумента = 0
	int				opcode;		// номер инструкции
	int				cycle;		// сколько циклов работает
	char			*full_name;	// типа описание инструкции
	int				coding_byte;// codage octal: true false
	int				two_bytes;	// вот это я не понял
}				t_op;

typedef	struct	s_param
{
	unsigned int	value;		//значения аргумента
	char			*label;		//значение
	int				type;		//тип аргумента:T_REG = 1; T_DIR = 2; T_IND = 3;
	struct s_param	*next;		//ссылка на след аргумент
}				t_param;

typedef struct	s_ins
{
	char			*name;		// имя инструкции
	t_param			*param;		// данные аргументов инструкции
	int				codage;		// codage octal: true false
	char			*opcode;	// имя инструкц в хексе, мб это не надо?
	char 			*label;		//имя лэйбла
	unsigned int	size;		//длинна всей инструкции, по дефолту = 0
	unsigned int	pos;		//позиция инструкц, по дефолту = 0
	struct s_ins			*next;
}				t_ins;

#endif